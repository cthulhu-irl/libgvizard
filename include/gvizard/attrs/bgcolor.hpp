#ifndef GVIZARD_ATTRS_BGCOLOR_HPP_
#define GVIZARD_ATTRS_BGCOLOR_HPP_

#include <optional>
#include <variant>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/color.hpp>

namespace gvizard::attrs {

template <typename GradientType = attrtypes::ColorType>
using BGColorValueType =
  std::optional<std::variant<attrtypes::ColorType, GradientType>>;

struct BGColor final
  : public AttributeBase<BGColor, BGColorValueType<attrtypes::ColorType>>
{
  using value_type = BGColorValueType<attrtypes::ColorType>;

  constexpr static const char * const name = "bgcolor";

  constexpr explicit BGColor() : AttributeBase() {}
  constexpr explicit BGColor(const value_type& value)
    : AttributeBase(value)
  {}
  constexpr explicit BGColor(value_type&& value)
    : AttributeBase(std::move(value))
  {}

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

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_BGCOLOR_HPP_
