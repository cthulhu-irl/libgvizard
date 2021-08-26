#ifndef GVIZARD_ATTRS_COLOR_HPP_
#define GVIZARD_ATTRS_COLOR_HPP_

#include <optional>
#include <variant>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/color.hpp>

#include <gvizard/colors/x11.hpp>
#include <gvizard/colors/rgba.hpp>

#include <gvizard/colors/color.hpp>

namespace gvizard::attrs {

template <typename ColorT>
using ColorValType = std::variant<ColorT, attrtypes::ColorList<ColorT>>;

struct Color final
  : public AttributeBase<Color, ColorValType<attrtypes::ColorType>>
{
  using value_type = ColorValType<attrtypes::ColorType>;

  constexpr static const char * const name = "color";

  explicit Color() : AttributeBase() {}
  explicit Color(const value_type& value) : AttributeBase(value) {}
  explicit Color(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value()
  {
    return get_default_color();
  }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
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
