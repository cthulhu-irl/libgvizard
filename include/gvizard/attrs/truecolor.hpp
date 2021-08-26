#ifndef GVIZARD_ATTRS_TRUECOLOR_HPP_
#define GVIZARD_ATTRS_TRUECOLOR_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct TrueColor final : public AttributeBase<TrueColor, bool> {
  using value_type = bool;

  constexpr static const char * const name = "truecolor";

  constexpr explicit TrueColor() noexcept : AttributeBase() {}
  constexpr explicit TrueColor(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_TRUECOLOR_HPP_
