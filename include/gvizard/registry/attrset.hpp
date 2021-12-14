#ifndef GVIZARD_ATTRIBUTESET_HPP_
#define GVIZARD_ATTRIBUTESET_HPP_

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "mtputils.hpp"

namespace gvizard {

template <typename ...Ts>
class AttributeSet {
  using storage_type = std::tuple<Ts...>;

  storage_type attrs_;

 public:
  struct aggregate_tag {};

  constexpr explicit AttributeSet() : attrs_{} {}

  constexpr explicit AttributeSet(storage_type storage)
    : attrs_{std::move(storage)}
  {}

  template <typename ...Attrs>
  constexpr explicit AttributeSet(aggregate_tag, Attrs... attrs)
    : attrs_{std::move(attrs...)}
  {}

  constexpr std::size_t count() const noexcept
  {
    return sizeof...(Ts);
  }

  template <typename Attr>
  constexpr auto& get() & noexcept
  {
    return std::get<Attr>(attrs_);
  }

  template <typename Attr>
  constexpr const auto& get() const& noexcept
  {
    return std::get<Attr>(attrs_);
  }

  template <typename Attr>
  constexpr auto&& get() && noexcept
  {
    return std::move(std::get<Attr>(attrs_));
  }

  template <typename Attr>
  constexpr const auto& get() const&& noexcept
  {
    return std::move(std::get<Attr>(attrs_));
  }

  template <typename ...Attrs>
  constexpr auto subset() &
  {
    return AttributeSet<Attrs...>(aggregate_tag{}, get<Attrs>()...);
  }

  template <typename ...Attrs>
  constexpr auto subset() const&
  {
    return AttributeSet<Attrs...>(aggregate_tag{}, get<Attrs>()...);
  }

  template <typename ...Attrs>
  constexpr auto subset() &&
  {
    return AttributeSet<Attrs...>(
        aggregate_tag{},
        std::move(get<Attrs>())...
    );
  }

  template <typename ...Attrs>
  constexpr auto subset() const&&
  {
    return AttributeSet<Attrs...>(
        aggregate_tag{},
        std::move(get<Attrs>())...
    );
  }

  template <typename Attr, typename F>
  constexpr auto update(F&& func)
    noexcept(noexcept(func(std::declval<Attr&>())))
  {
    return func(get<Attr>());
  }

  template <typename ...Attrs, typename ...UAttrs>
  constexpr void set(UAttrs&&... attrs)
  {
    static_assert(
        sizeof...(Attrs) == sizeof...(UAttrs),
        "given arguments aren't as many as given attribute types"
    );  

    static_assert(
        (std::is_assignable<Attrs&, UAttrs>::value && ...),
        "given attributes types aren't assignable from given arguments"
    );  

    ((std::get<Attrs>(attrs_) = std::forward<UAttrs>(attrs)), ...);
    return *this;
  }

  template <typename Attr>
  constexpr bool has() const noexcept
  {
    return mtp::has_type_in_v<Attr, Ts...>;
  }

  template <typename Attr>
  constexpr auto remove() { get<Attr>() = Attr(); }
};

}  // namespace gvizard

#endif  // GVIZARD_ATTRIBUTESET_HPP_
