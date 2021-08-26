#ifndef GVIZARD_ATTRS_DAMPING_HPP_
#define GVIZARD_ATTRS_DAMPING_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Damping final : public AttributeBase<Damping, double> {
  using value_type = double;

  constexpr static const char * const name = "damping";

  constexpr explicit Damping() : AttributeBase() {}
  constexpr explicit Damping(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 0.99;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DAMPING_HPP_
