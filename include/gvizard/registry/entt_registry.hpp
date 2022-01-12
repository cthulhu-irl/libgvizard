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

namespace gvizard {
namespace registry {

class EnTTRegistry {
 public:
  using entity_type = entt::entity;

 private:
  entt::registry registry_;

 public:
  constexpr std::size_t size() const noexcept
  {
    return registry_.size();
  }

  // this shouldn't be used.
  constexpr std::size_t max_size() const noexcept
  {
    return std::numeric_limits<uint32_t>::max();
  }

  constexpr auto& raw_registry() noexcept { return registry_; }
  constexpr const auto& raw_registry() const noexcept { return registry_; }

  constexpr entity_type create()
  {
    return registry_.create();
  }

  constexpr bool destroy(entity_type entity)
  {
    return registry_.destroy(entity);
  }

  void clear()
  {
    std::vector<entity_type> entities{};

    entities.reserve(registry_.size());

    registry_.each([&entities](auto entity) {
      entities.push_back(entity);
    });

    registry_.destroy(entities.cbegin(), entities.cend());
  }

  // -- Registry access (lookup/modify) methods --

  template <typename Attr>
  constexpr auto get(entity_type entity) noexcept
    -> utils::OptionalRef<Attr>
  {
    return registry_.get<Attr>(entity);
  }

  template <typename Attr>
  constexpr auto get(entity_type entity) const noexcept
    -> utils::OptionalRef<const Attr>
  {
    return registry_.get<Attr>(entity);
  }

  template <typename Attr, typename ...Rest>
  constexpr auto has(entity_type entity) const noexcept -> bool
  {
    return registry_.valid(entity)
        && registry_.all_of<Attr, Rest...>(entity);
  }

  template <typename Attr, typename F>
  constexpr auto update(entity_type entity, F&& func)
    -> utils::OptionalRef<Attr>
  {
    auto& attr = registry_.get<Attr>(entity);
    func(attr);
    return attr;
  }

  template <typename Attr, typename ValT>
  constexpr auto set(entity_type entity, ValT&& value)
    -> utils::OptionalRef<Attr>
  {
    return
      registry_.emplace_or_replace<Attr>(entity, std::forward<ValT>(value));
  }

  template <typename Attr, typename ...Args>
  constexpr auto emplace(entity_type entity, Args&&... args)
    -> utils::OptionalRef<Attr>
  {
    return registry_.emplace<Attr>(entity, std::forward<Args>(args)...);
  }

  template <typename Attr>
  constexpr auto remove(entity_type entity) -> bool
  {
    if (!has<Attr>(entity))
      return false;

    registry_.clear<Attr>(entity);
    return true;
  }
};

}  // namespace registry
}  // namespace gvizard

#endif  // GVIZARD_REGISTRY_ENTT_REGISTRY_HPP_
