#ifndef GVIZARD_ATTRS_NSLIMIT1_HPP_
#define GVIZARD_ATTRS_NSLIMIT1_HPP_

#include <optional>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct NSLimit1 final
  : public AttributeBase<NSLimit1, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "nslimit1";

  constexpr explicit NSLimit1() noexcept : AttributeBase() {}
  constexpr explicit NSLimit1(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_NSLIMIT1_HPP_
