#ifndef GVIZARD_ATTRS_CONCENTRATE_HPP_
#define GVIZARD_ATTRS_CONCENTRATE_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Concentrate final : public AttributeBase<Concentrate, bool> {
  using value_type = bool;

  constexpr static const char * const name = "concentrate";

  constexpr explicit Concentrate() noexcept : AttributeBase() {}
  constexpr explicit Concentrate(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CONCENTRATE_HPP_
