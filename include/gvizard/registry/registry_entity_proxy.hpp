#ifndef GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_
#define GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_

#include <utility>

#include "gvizard/utils.hpp"

namespace gviz::registry {

template <typename Registry>
class RegistryEntityProxy {
 public:
  using entity_type = typename Registry::entity_type;

 private:
  Registry&   registry_;
  entity_type entity_;

 public:
  RegistryEntityProxy(Registry& registry, entity_type entity)
    : registry_(registry)
    , entity_(std::move(entity))
  {}

  template <typename Attr>
  auto get() -> utils::OptionalRef<Attr>
  {
    return registry_.template get<Attr>(entity_);
  }

  template <typename Attr>
  auto get() const -> utils::OptionalRef<const Attr>
  {
    return registry_.template get<Attr>(entity_);
  }

  template <typename Attr>
  bool has() const { return registry_.template has<Attr>(entity_); }

  template <typename Attr, typename F>
  bool update(F&& func)
  {
    return registry_.template update<Attr>(entity_, std::forward<F>(func));
  }

  template <typename Attr, typename ValT>
  auto set(ValT&& value) -> utils::OptionalRef<Attr>
  {
    return registry_.template set<Attr>(entity_, std::forward<ValT>(value));
  }

  template <typename Attr, typename ...Args>
  auto emplace(Args&&... args) -> utils::OptionalRef<Attr>
  {
    return registry_.template emplace(entity_, std::forward<Args>(args)...);
  }

  template <typename Attr>
  bool remove() { return registry_.template remove<Attr>(entity_); }
};

}  // namespace gviz::registry

#endif  // GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_
