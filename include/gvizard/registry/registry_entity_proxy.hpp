#ifndef GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_
#define GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_

#include "gvizard/utils.hpp"
#include <utility>

namespace gviz::registry {

template <typename Registry>
class RegistryEntityProxy {
 public:
  using entity_type = typename Registry::entity_type;

 private:
  utils::Ref<Registry> registry_;
  entity_type          entity_;

 public:
  RegistryEntityProxy(utils::Ref<Registry> registry, entity_type entity)
    : registry_(std::move(registry))
    , entity_(std::move(entity_))
  {}

  template <typename Attr>
  auto& get() { return registry_->template get<Attr>(entity_); }

  template <typename Attr>
  const auto& get() const { return registry_->template get<Attr>(entity_); }

  template <typename Attr>
  bool has() const { return registry_->template has<Attr>(entity_); }

  template <typename Attr, typename F>
  auto update(F&& func)
  {
    return registry_->template update<Attr>(entity_, std::forward<F>(func));
  }

  template <typename Attr, typename ValT>
  auto set(ValT&& value)
  {
    return registry_->template set<Attr>(entity_, std::forward<ValT>(value));
  }

  template <typename Attr, typename ...Args>
  auto emplace(Args&&... args)
  {
    return registry_->template emplace(entity_, std::forward<Args>(args)...);
  }

  template <typename Attr>
  auto remove() { return registry_->template remove<Attr>(entity_); }
};

}  // namespace gviz::registry

#endif  // GVIZARD_REGISTRY_REGISTRY_ENTITY_PROXY_HPP_
