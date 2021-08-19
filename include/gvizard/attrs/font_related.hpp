#ifndef GVIZARD_ATTRS_FONT_RELATED_HPP_
#define GVIZARD_ATTRS_FONT_RELATED_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/color.hpp>
#include <gvizard/colors/x11.hpp>

namespace gvizard::attrs {

struct FontColor final
  : public AttributeBase<FontColor, attrtypes::ColorType>
{
  using value_type = attrtypes::ColorType;

  constexpr static const char * const name = "fontcolor";

  constexpr explicit FontColor() : AttributeBase() {}
  constexpr explicit FontColor(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return {colors::X11ColorEnum::black};
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_FONT_RELATED_HPP_
