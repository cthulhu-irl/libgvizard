#ifndef GVIZARD_ATTRS_NODESEP_HPP_
#define GVIZARD_ATTRS_NODESEP_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct NodeSep final : public AttributeBase<NodeSep, double> {
  using value_type = double;

  constexpr static const char * const name = "nodesep";

  constexpr explicit NodeSep() noexcept : AttributeBase() {}
  constexpr explicit NodeSep(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return .25; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= .02;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_NODESEP_HPP_
