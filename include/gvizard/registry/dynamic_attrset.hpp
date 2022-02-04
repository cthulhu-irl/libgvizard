#ifndef GVIZARD_REGISTRY_DYNAMIC_ATTRSET_HPP_
#define GVIZARD_REGISTRY_DYNAMIC_ATTRSET_HPP_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <any>
#include <optional>
#include <unordered_map>
#include <utility>

#include "gvizard/utils.hpp"
#include "gvizard/mtputils.hpp"

namespace gviz {
namespace registry {

template <typename ...Attrs>
class LimitedTypeSet final {
  constexpr static std::size_t types_count = sizeof...(Attrs);
  constexpr static std::size_t types_index_arr[types_count] = { 0 };

 public:
  using typekey_type = std::size_t;

  template <typename T>
  constexpr auto get_type_key() const noexcept
    -> std::optional<typekey_type>
  {
    constexpr auto ret = mtp::find_type_index_in_v<T, Attrs...>;
    if constexpr (ret == 0)
      return std::nullopt;

    return ret - 1;
  }

  constexpr auto get_type_index_bykey(typekey_type typekey) noexcept
    -> std::optional<std::size_t>
  {
    if (typekey >= types_count)
      return std::nullopt;

    return types_index_arr[typekey];
  }

  template <typename T>
  constexpr auto get_type_index() noexcept -> std::optional<std::size_t>
  {
    constexpr auto typekey = get_type_key<T>();
    if constexpr (!typekey.has_value())
      return std::nullopt;

    return types_index_arr[typekey];
  }

  constexpr auto set_type_index_bykey(
                  typekey_type typekey, std::size_t index) const noexcept
    -> bool
  {
    if (typekey >= types_count)
      return false;

    types_index_arr[typekey] = index;

    return true;
  }

  template <typename T>
  constexpr auto set_type_index(std::size_t index) const noexcept -> bool
  {
    constexpr auto typekey = get_type_key<T>();
    if constexpr (!typekey.has_value())
      return false;

    types_index_arr[typekey] = index;

    return true;
  }

  constexpr auto set_type_index_once_bykey(
                  typekey_type typekey, std::size_t index) const noexcept
    -> bool
  {
    if (typekey >= types_count)
      return false;

    if (types_index_arr[typekey] != 0)
      return false;

    types_index_arr[typekey] = index;

    return true;
  }

  template <typename T>
  constexpr auto set_type_index_once(std::size_t index) noexcept -> bool
  {
    constexpr auto typekey = get_type_key<T>();
    if constexpr (!typekey.has_value())
      return false;

    if (types_index_arr[typekey] != 0)
      return false;

    types_index_arr[typekey] = index;

    return true;
  }

  constexpr auto pop_type_index_bykey(typekey_type typekey) noexcept
    -> bool
  {
    if (typekey >= types_count)
      return false;

    types_index_arr[typekey] = 0;

    return true;
  }

  template <typename T>
  constexpr auto pop_type_index() noexcept -> bool
  {
    constexpr auto typekey = get_type_key<T>();
    if constexpr (!typekey.has_value())
      return false;

    types_index_arr[typekey] = 0;

    return true;
  }
};

class UnlimitedTypeSet final {
 public:
  using typekey_type = std::type_index;

 private:
  std::unordered_map<typekey_type, std::size_t> map_;

 public:
  template <typename T>
  auto get_type_key() const noexcept -> std::optional<typekey_type>
  {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
    return std::type_index(typeid(type));
  }

  auto get_type_index_bykey(typekey_type typekey) const
    -> std::optional<std::size_t>
  {
    const auto found = map_.find(typekey);
    if (found == map_.end())
      return std::nullopt;

    return found->second;
  }

  template <typename T>
  auto get_type_index() const -> std::optional<std::size_t>
  {
    return get_type_index_bykey(get_type_key<T>().value());
  }

  auto set_type_index_bykey(typekey_type typekey, std::size_t index)
    -> bool
  {
    map_[typekey] = index;
    return true;
  }

  template <typename T>
  auto set_type_index(std::size_t index) -> bool
  {
    return set_type_index(get_type_key<T>().value(), index);
  }

  auto set_type_index_once_bykey(
              typekey_type typekey, std::size_t index) -> bool
  {
    if (map_.find(typekey) == map_.end())
      return false;

    map_[typekey] = index;
    return true;
  }

  template <typename T>
  auto set_type_index_once(std::size_t index) -> bool
  {
    return set_type_index_once(get_type_key<T>().value(), index);
  }

  auto pop_type_index_bykey(typekey_type typekey) -> bool
  {
    auto found = map_.find(typekey);
    if (found == map_.end())
      return false;

    map_.erase(found);
    return true;
  }

  template <typename T>
  auto pop_type_index() -> bool
  {
    return pop_type_index_bykey(get_type_key<T>().value());
  }
};

template <typename TypeSetManager,
          typename Allocator = std::allocator<std::any>>
class DynamicAttrSet final {
  using typekey_type = typename TypeSetManager::typekey_type;

  struct AttrPair {
    typekey_type typekey;
    std::any     attr;
  };

  using vector_type = std::vector<AttrPair, Allocator>;

  vector_type    vector_;
  TypeSetManager typeset_{};

 public:
  constexpr explicit DynamicAttrSet() {}
  constexpr explicit DynamicAttrSet(Allocator allocator)
    : vector_(allocator)
  {}

  constexpr auto size() const noexcept -> std::size_t
  {
    return vector_.size();
  }

  constexpr auto max_size() const noexcept -> std::size_t
  {
    return vector_.max_size();
  }

  template <typename Attr>
  constexpr auto get() -> utils::OptionalRef<Attr>
  {
    const auto index = typeset_.template get_type_index<Attr>();
    if (!index.has_value())
      return utils::nulloptref;

    return vector_[index.value()];
  }

  template <typename Attr>
  constexpr auto get() const -> utils::OptionalRef<const Attr>
  {
    const auto index = typeset_.template get_type_index<Attr>();
    if (!index.has_value())
      return utils::nulloptref;

    return std::any_cast<Attr>(vector_[index.value()].attr);
  }

  template <typename Attr>
  constexpr auto has() const -> bool
  {
    return typeset_.template get_type_index<Attr>().has_value();
  }

  template <typename ...Attrs>
  constexpr auto reserve() -> bool
  {
    const auto count = reserve_typeset_set_once<Attrs...>();

    vector_.reserve(vector_.size() + count);

    return true;
  }

  template <typename Attr, typename F>
  constexpr auto update(F&& func)
    -> std::optional<std::invoke_result_t<F, Attr&>>
  {
    return get<Attr>().map([&func](auto& attr) { return func(attr); });
  }

  template <typename Attr>
  constexpr auto set(Attr attr) -> bool
  {
    if (!reserve<Attr>())
      return false;

    const auto index = typeset_.template get_type_index<Attr>().value();
    const auto typekey = typeset_.template get_type_key<Attr>().value();

    vector_[index] = AttrPair { typekey, std::move(attr) };

    return true;
  }

  template <typename Attr, typename ...Args>
  constexpr auto emplace(Args&&... args) -> bool
  {
    if (!reserve<Attr>())
      return false;

    const auto index = typeset_.template get_type_index<Attr>().value();
    const auto typekey = typeset_.template get_type_key<Attr>().value();

    // TODO check again... :/
    vector_.emplace(
      vector_.begin() + index,
      AttrPair { typekey, Attr(std::forward<Args>(args)...) }
    );

    return true;
  }

  template <typename Attr>
  constexpr auto remove() -> bool
  {
    const auto indexopt = typeset_.template get_type_index<Attr>();
    if (!indexopt.has_value())
      return false;

    const auto index = indexopt.value();
    const auto last_typekey = vector_.back().typekey;

    vector_[index] = std::move(vector_.back());
    vector_.pop_back();

    typeset_.template pop_type_index<Attr>();
    typeset_.template set_type_index_bykey(last_typekey, index);

    return true;
  }

 private:
  template <typename Attr, typename ...Attrs>
  constexpr auto reserve_typeset_set_once(std::size_t index)
    -> std::size_t
  {
    const std::size_t ret =
        typeset_.template set_type_index_once<Attr>(index);

    if constexpr (sizeof...(Attrs) == 0)
      return ret;

    return ret + int(reserve_typeset_set_once<Attrs...>(index + ret));
  }
};

}  // namespace registry
}  // namespace gviz

#endif  // GVIZARD_REGISTRY_DYNAMIC_ATTRSET_HPP_
