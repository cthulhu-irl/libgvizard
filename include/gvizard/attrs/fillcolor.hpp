#ifndef GVIZARD_ATTRS_FILLCOLOR_HPP_
#define GVIZARD_ATTRS_FILLCOLOR_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/color.hpp"
#include "gvizard/colors/x11.hpp"

namespace gvizard::attrs {

using FillColorType =
  std::variant<
    attrtypes::ColorType,
    attrtypes::ColorList<attrtypes::ColorType>>;

struct FillColor final : public AttributeBase<FillColor, FillColorType> {
  using value_type = FillColorType;

  constexpr static const char * const name = "fillcolor";

  explicit FillColor() noexcept : AttributeBase() {}
  explicit FillColor(const value_type& value) : AttributeBase(value) {}
  explicit FillColor(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept
  {
    return attrtypes::ColorType(
      colors::X11Color{colors::X11ColorEnum::lightgrey}
    );
  }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_FILLCOLOR_HPP_
