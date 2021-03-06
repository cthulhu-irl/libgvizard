#ifndef GVIZARD_ATTRS_RESOLUTION_HPP_
#define GVIZARD_ATTRS_RESOLUTION_HPP_

#include <optional>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Resolution final
  : public AttributeBase<Resolution, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "resolution";

  constexpr explicit Resolution() noexcept : AttributeBase() {}
  constexpr explicit Resolution(value_type value) : AttributeBase(value) {}

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

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_RESOLUTION_HPP_
