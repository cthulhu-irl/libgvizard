#ifndef GVIZARD_REGISTRY_ENTT_REGISTRY_HPP_
#define GVIZARD_REGISTRY_ENTT_REGISTRY_HPP_

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>
#include <utility>

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>

#include "gvizard/utils.hpp"

namespace gviz {
namespace registry {

class EnTTRegistry {
 public:
  using entity_type = entt::entity;

 private:
  entt::registry registry_;
  std::size_t    count_; /// count of valid entities in registry.

 public:
  std::size_t size() const noexcept
  {
    // return registry_.size(); // returns entities created so far... so no.
    return count_;
  }

  // this shouldn't be used.
  constexpr std::size_t max_size() const noexcept
  {
    return std::numeric_limits<uint32_t>::max();
  }

  auto& raw_registry() noexcept { return registry_; }
  const auto& raw_registry() const noexcept { return registry_; }

  entity_type create()
  {
    ++count_;
    return registry_.create();
  }

  void destroy(entity_type entity)
  {
    if (registry_.valid(entity)) {
      registry_.destroy(entity);
      --count_;
    }
  }

  void clear()
  {
    registry_.clear();
    count_ = 0;
  }

  // -- Registry access (lookup/modify) methods --

  template <typename Attr>
  auto get(entity_type entity) noexcept -> utils::OptionalRef<Attr>
  {
    if (!has<Attr>(entity))
      return utils::nulloptref;

    return registry_.template get<Attr>(entity);
  }

  template <typename Attr>
  auto get(entity_type entity) const noexcept -> utils::OptionalRef<const Attr>
  {
    if (!has<Attr>(entity))
      return utils::nulloptref;

    return registry_.template get<Attr>(entity);
  }

  template <typename Attr, typename ...Rest>
  bool has(entity_type entity) const noexcept
  {
    return registry_.valid(entity)
        && registry_.template all_of<Attr, Rest...>(entity);
  }

  template <typename Attr, typename F>
  bool update(entity_type entity, F&& func)
  {
    if (!has<Attr>(entity))
      return false;

    auto& attr = registry_.template get<Attr>(entity);
    func(attr);
    return true;
  }

  template <typename Attr, typename ValT>
  auto set(entity_type entity, ValT&& value) -> utils::OptionalRef<Attr>
  {
    if (!registry_.valid(entity))
      return utils::nulloptref;

    return registry_.template emplace_or_replace<Attr>(
      entity,
      std::forward<ValT>(value)
    );
  }

  template <typename Attr, typename ...Args>
  auto emplace(entity_type entity, Args&&... args) -> utils::OptionalRef<Attr>
  {
    if (!registry_.valid(entity))
      return utils::nulloptref;

    return registry_.template emplace<Attr>(
      entity,
      std::forward<Args>(args)...
    );
  }

  template <typename Attr>
  bool remove(entity_type entity)
  {
    if (!has<Attr>(entity))
      return false;

    registry_.template remove<Attr>(entity);
    return true;
  }
};

}  // namespace registry
}  // namespace gviz

#endif  // GVIZARD_REGISTRY_ENTT_REGISTRY_HPP_
