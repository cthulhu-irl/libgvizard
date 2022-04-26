#ifndef GVIZARD_ATTRS_COLORSCHEME_HPP_
#define GVIZARD_ATTRS_COLORSCHEME_HPP_

#include <string>

#include "gvizard/utils.hpp"

#include "gvizard/attribute.hpp"
#include "gvizard/colors/general.hpp"

namespace gviz::attrs {

struct ColorScheme final
  : public AttributeBase<ColorScheme, colors::SchemeEnum>
{
  using value_type = colors::SchemeEnum;

  constexpr static const char * const name = "colorscheme";

  constexpr explicit ColorScheme() noexcept : AttributeBase() {}
  constexpr explicit ColorScheme(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return colors::SchemeEnum::X11;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return true;
  }

  operator std::string() const
  {
    return std::string(
      utils::EnumHelper<colors::SchemeEnum>::to_str(value_)
    );
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_COLORSCHEME_HPP_
