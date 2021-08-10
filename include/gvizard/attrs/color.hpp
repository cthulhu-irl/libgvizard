#ifndef GVIZARD_ATTRS_COLOR_HPP_
#define GVIZARD_ATTRS_COLOR_HPP_

#include <optional>
#include <variant>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/color.hpp"

#include "gvizard/colors/x11.hpp"
#include "gvizard/colors/rgba.hpp"

#include "gvizard/colors/color.hpp"

namespace gvizard::attrs {

template <typename ColorT>
using ColorValType = std::variant<ColorT, attrtypes::ColorList<ColorT>>;

struct Color final
  : public AttributeBase<Color, ColorValType<attrtypes::ColorType>>
{
  using value_type = ColorValType<attrtypes::ColorType>;

  constexpr static const char * const name = "color";

  Color() : AttributeBase(get_default_value()) {}
  Color(const value_type& value) : AttributeBase(value) {}
  Color(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value()
  {
    return get_default_color();
  }

  static bool is_default(const value_type& value)
  {
    auto pval = std::get_if<attrtypes::ColorType>(&value);
    if (!pval) return false;

    // NOTE inaccurate a bit when given HSV
    auto rgba = std::get<attrtypes::ColorType>(value).as<colors::RGBA>();

    return rgba == get_default_color().as<colors::RGBA>();
  }

  static bool constraint(const value_type& value) { return true; }

 private:
  static attrtypes::ColorType get_default_color()
  {
    return attrtypes::ColorType(
      colors::X11Color(colors::X11ColorEnum::black)
    );
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_COLOR_HPP_
