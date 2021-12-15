#ifndef GVIZARD_ATTRS_ROTATE_HPP_
#define GVIZARD_ATTRS_ROTATE_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Rotate final : public AttributeBase<Rotate, int> {
  using value_type = int;

  constexpr static const char * const name = "rotate";

  constexpr explicit Rotate() noexcept : AttributeBase() {}
  constexpr explicit Rotate(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_ROTATE_HPP_
