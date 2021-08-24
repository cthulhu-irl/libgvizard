#ifndef GVIZARD_ATTRS_PENCOLOR_HPP_
#define GVIZARD_ATTRS_PENCOLOR_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/color.hpp>
#include <gvizard/colors/x11.hpp>

namespace gvizard::attrs {

struct PenColor final
  : public AttributeBase<PenColor, attrtypes::ColorType>
{
  using value_type = attrtypes::ColorType;

  constexpr static const char * const name = "pencolor";

  constexpr explicit PenColor() : AttributeBase() {}
  constexpr explicit PenColor(value_type value) : AttributeBase(value) {}

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

#endif  // GVIZARD_ATTRS_PENCOLOR_HPP_
