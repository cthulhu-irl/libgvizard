#ifndef GVIZARD_ATTRS_SIDES_HPP_
#define GVIZARD_ATTRS_SIDES_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Sides final : public AttributeBase<Sides, int> {
  using value_type = int;

  constexpr static const char * const name = "sides";

  constexpr explicit Sides() noexcept : AttributeBase() {}
  constexpr explicit Sides(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 4; }

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

#endif  // GVIZARD_ATTRS_SIDES_HPP_
