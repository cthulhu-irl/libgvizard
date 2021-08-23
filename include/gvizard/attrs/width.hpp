#ifndef GVIZARD_ATTRS_WIDTH_HPP_
#define GVIZARD_ATTRS_WIDTH_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Width final : public AttributeBase<Width, double> {
  using value_type = double;

  constexpr static const char * const name = "width";

  constexpr explicit Width() : AttributeBase() {}
  constexpr explicit Width(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.75; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.01;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_WIDTH_HPP_
