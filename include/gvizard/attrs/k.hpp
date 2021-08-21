#ifndef GVIZARD_ATTRS_K_HPP_
#define GVIZARD_ATTRS_K_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Kvalue final : public AttributeBase<Kvalue, double> {
  using value_type = double;

  constexpr static const char * const name = "K";

  constexpr explicit Kvalue() : AttributeBase(get_default_value()) {}
  constexpr explicit Kvalue(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.3; }

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

#endif  // GVIZARD_ATTRS_K_HPP_
