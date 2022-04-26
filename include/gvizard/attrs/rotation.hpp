#ifndef GVIZARD_ATTRS_ROTATION_HPP_
#define GVIZARD_ATTRS_ROTATION_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Rotation final : public AttributeBase<Rotation, double> {
  using value_type = double;

  constexpr static const char * const name = "rotation";

  constexpr explicit Rotation() noexcept : AttributeBase() {}
  constexpr explicit Rotation(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_ROTATION_HPP_
