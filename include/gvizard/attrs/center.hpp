#ifndef GVIZARD_ATTRS_CENTER_HPP_
#define GVIZARD_ATTRS_CENTER_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Center : public AttributeBase<Center, bool> {
  using value_type = bool;

  constexpr static const char * const name = "center";

  constexpr Center() : AttributeBase(get_default_value()) {}
  constexpr Center(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CENTER_HPP_