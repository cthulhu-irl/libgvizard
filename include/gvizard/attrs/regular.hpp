#ifndef GVIZARD_ATTRS_REGULAR_HPP_
#define GVIZARD_ATTRS_REGULAR_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Regular final : public AttributeBase<Regular, bool> {
  using value_type = bool;

  constexpr static const char * const name = "regular";

  constexpr explicit Regular() noexcept : AttributeBase() {}
  constexpr explicit Regular(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_REGULAR_HPP_
