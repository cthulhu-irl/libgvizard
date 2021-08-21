#ifndef GVIZARD_ATTRS_HEIGHT_HPP_
#define GVIZARD_ATTRS_HEIGHT_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Height final : public AttributeBase<Height, double> {
  using value_type = double;

  constexpr static const char * const name = "height";

  constexpr explicit Height() : AttributeBase() {}
  constexpr explicit Height(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 0.5;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.02;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_HEIGHT_HPP_
