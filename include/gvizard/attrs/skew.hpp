#ifndef GVIZARD_ATTRS_SKEW_HPP_
#define GVIZARD_ATTRS_SKEW_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Skew final : public AttributeBase<Skew, double> {
  using value_type = double;

  constexpr static const char * const name = "skew";

  constexpr explicit Skew() noexcept : AttributeBase() {}
  constexpr explicit Skew(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= -100.;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SKEW_HPP_
