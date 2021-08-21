#ifndef GVIZARD_ATTRS_CLUSTERRANK_HPP_
#define GVIZARD_ATTRS_CLUSTERRANK_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/clustermode.hpp"

namespace gvizard::attrs {

struct ClusterRank final
  : public AttributeBase<ClusterRank, attrtypes::ClusterMode>
{
  using value_type = attrtypes::ClusterMode;

  constexpr static const char * const name = "clusterrank";

  constexpr explicit ClusterRank() : AttributeBase() {}
  constexpr explicit ClusterRank(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::ClusterMode::local;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CLUSTERRANK_HPP_
