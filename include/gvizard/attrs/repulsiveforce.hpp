#ifndef GVIZARD_ATTRS_REPULSIVEFORCE_HPP_
#define GVIZARD_ATTRS_REPULSIVEFORCE_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct RepulsiveForce final : public AttributeBase<RepulsiveForce, double>
{
  using value_type = double;

  constexpr static const char * const name = "repulsiveforce";

  constexpr explicit RepulsiveForce() noexcept : AttributeBase() {}
  constexpr explicit RepulsiveForce(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return 1.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_REPULSIVEFORCE_HPP_
