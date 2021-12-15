#ifndef GVIZARD_ATTRS_VORO_MARGIN_HPP_
#define GVIZARD_ATTRS_VORO_MARGIN_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct VoroMargin final : public AttributeBase<VoroMargin, double> {
  using value_type = double;

  constexpr static const char * const name = "voro_margin";

  constexpr explicit VoroMargin() noexcept : AttributeBase() {}
  constexpr explicit VoroMargin(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.05; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_VORO_MARGIN_HPP_
