#ifndef GVIZARD_REGISTRY_ATTRSET_REGISTRY_HPP_
#define GVIZARD_REGISTRY_ATTRSET_REGISTRY_HPP_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <optional>

#include "gvizard/utils.hpp"

namespace gvizard {
namespace registry {

template <typename AttrSetT>
class AttrSetRegistry {
 public:
  using entity_type = std::size_t;

  struct AttrSetPair {
    entity_type entity;
    AttrSetT    attrset;
  };

  using attrset_type = AttrSetPair;

 private:
  using index_type = std::size_t;

  std::vector<attrset_type>                   vector_;
  std::unordered_map<entity_type, index_type> entity_index_map_;
  entity_type                                 last_entity_;

 public:
  explicit AttrSetRegistry() : vector_{} {}
  explicit AttrSetRegistry(std::vector<attrset_type> vec)
    : vector_(std::move(vec))
  {}
  explicit AttrSetRegistry(std::initializer_list<attrset_type> lst)
    : vector_(lst)
  {}

  auto size() noexcept -> std::size_t
  {
    return entity_index_map_.size();
  }

  constexpr auto max_size() -> std::size_t
  {
    return std::numeric_limits<std::size_t>::max();
  }

  void clear() noexcept
  {
    entity_index_map_.clear();
    vector_.clear();
  }

  auto create(attrset_type attrset = {}) noexcept -> entity_type
  {
    const auto index = vector_.size();

    // there shouldn't be that many allocated entities
    // that it wouldn't find any available number.
    while (!entity_index_map_.try_emplace(++last_entity_, index).second);

    vector_.push_back(AttrSetPair{ last_entity_, std::move(attrset) });

    return last_entity_;
  }

  // place last item in entities into its place, update index map,
  // and shrink the vector.
  auto destroy(entity_type entity) -> bool
  {
    if (vector_.size() == 0)
      return false;

    auto found_index_iter = entity_index_map_.find(entity);
    if (found_index_iter == entity_index_map_.end())
      return false;

    const auto recycle_index = found_index_iter->second;
    const auto last_index = vector_.size() - 1;

    entity_index_map_.erase(found_index_iter);

    // if it's already the last item, pop it and return.
    // going further is both heavy and would leave a leak/vuln for UAF.
    if (recycle_index == last_index) {
      vector_.pop_back();
      return true;
    }

    const auto last_index_entity = vector_.back().entity;

    vector_[recycle_index] = std::move(vector_.back());
    entity_index_map_[last_index_entity] = recycle_index;

    vector_.pop_back();

    return true;
  }

  auto begin() noexcept { return vector_.begin(); }
  auto end() noexcept   { return vector_.end();   }

  auto cbegin() const noexcept { return vector_.cbegin(); }
  auto cend() const noexcept   { return vector_.cend();   }

  // -- AttrSet access (lookup/modify) methods --

  template <typename Attr>
  auto get(entity_type entity) noexcept -> utils::OptionalRef<Attr>
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return std::nullopt;

    return attrsetopt->template get<Attr>();
  }

  template <typename Attr>
  auto get(entity_type entity) const noexcept
    -> utils::OptionalRef<const Attr>
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return std::nullopt;

    return attrsetopt->template get<Attr>();
  }

  template <typename Attr>
  auto has(entity_type entity) const noexcept -> bool
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return false;

    return attrsetopt->template has<Attr>();
  }

  template <typename Attr, typename F>
  auto update(entity_type entity, F&& func) -> utils::OptionalRef<Attr>
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return std::nullopt;

    return attrsetopt->template update<Attr>(std::forward<F>(func));
  }

  template <typename Attr, typename ValT>
  auto set(entity_type entity, ValT&& value) -> utils::OptionalRef<Attr>
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return std::nullopt;

    return attrsetopt->template set<Attr>(std::forward<ValT>(value));
  }

  template <typename Attr, typename ...Args>
  auto emplace(entity_type entity, Args&&... args)
    -> utils::OptionalRef<Attr>
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return std::nullopt;

    return attrsetopt->template emplace<Attr>(std::forward<Args>(args)...);
  }

  template <typename Attr>
  auto remove(entity_type entity) -> bool
  {
    auto attrsetopt = get_entity_attrset(entity);
    if (!attrsetopt)
      return false;

    return attrsetopt->template remove<Attr>();
  }

 private:
  // NOTE must be used only within access functions' scope and lifetime.
  auto get_entity_index(entity_type entity) const noexcept
    -> std::optional<index_type>
  {
    auto found_index_iter = entity_index_map_.find(entity);
    if (found_index_iter == entity_index_map_.end())
      return std::nullopt;

    return found_index_iter->second;
  }

  // NOTE must be used only within access functions' scope and lifetime.
  auto get_entity_attrset(entity_type entity) noexcept
    -> utils::OptionalRef<AttrSetT>
  {
    const auto index_opt = get_entity_index(entity);
    if (!index_opt.has_value())
      return utils::nulloptref;

    return vector_[index_opt.value()].attrset;
  }
};

}  // namespace registry
}  // namespace gvizard

#endif  // GVIZARD_REGISTRY_ATTRSET_REGISTRY_HPP_
