#ifndef GVIZARD_ATTRS_PIN_HPP_
#define GVIZARD_ATTRS_PIN_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Pin final : public AttributeBase<Pin, bool> {
  using value_type = bool;

  constexpr static const char * const name = "pin";

  constexpr explicit Pin() noexcept : AttributeBase() {}
  constexpr explicit Pin(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_PIN_HPP_
