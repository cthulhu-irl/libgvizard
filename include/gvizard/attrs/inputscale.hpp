#ifndef GVIZARD_ATTRS_INPUTSCALE_HPP_
#define GVIZARD_ATTRS_INPUTSCALE_HPP_

#include <optional>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct InputScale final
  : public AttributeBase<InputScale, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "inputscale";

  constexpr explicit InputScale() noexcept : AttributeBase() {}
  constexpr explicit InputScale(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return !value;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_INPUTSCALE_HPP_
