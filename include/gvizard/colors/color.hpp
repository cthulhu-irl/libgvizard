#ifndef GVIZARD_COLORS_COLOR_HPP_
#define GVIZARD_COLORS_COLOR_HPP_

#include <variant>
#include <vector>

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"
#include "gvizard/colors/x11.hpp"
#include "gvizard/colors/svg.hpp"

#include "gvizard/colors/general.hpp"
#include "gvizard/colors/converter.hpp"

namespace gvizard {

namespace colors {

struct Color {
  using color_variant_t =
    std::variant<
      RGB, RGBA, HSV, X11Color, SVGColor, X11ColorEnum, SVGColorEnum,
      SchemeColor<RGB>, SchemeColor<RGBA>, SchemeColor<HSV>,
      SchemeColor<X11Color>, SchemeColor<SVGColor>,
      SchemeColor<X11ColorEnum>, SchemeColor<SVGColorEnum>
    >;

  color_variant_t color;

  constexpr Color(const color_variant_t& clr) : color(clr) {}

  constexpr static std::optional<Color>
  make_rgb(RGB::octet_t r, RGB::octet_t g, RGB::octet_t b) noexcept
  {
    return Color{ RGB{ r, g, b } };
  }

  constexpr static std::optional<Color>
  make_rgba(
    RGBA::octet_t r,
    RGBA::octet_t g,
    RGBA::octet_t b,
    RGBA::octet_t a) noexcept
  {
    return Color{ RGBA{ r, g, b, a } };
  }

  constexpr static std::optional<Color>
  make_hsv(HSV::octet_t h, HSV::octet_t s, HSV::octet_t v) noexcept
  {
    auto hsv = HSV::make(h, s, v);
    if (!hsv.has_value())
      return std::nullopt;

    return Color{ hsv.value() };
  }

  template <typename T>
  constexpr T as() const noexcept
  {
    return std::visit(ColorConverterCallable<T>{}, color);
  }

  constexpr bool operator==(const Color& other) const
  {
    return as<HSV>() == other.as<HSV>();
  }

  constexpr bool operator!=(const Color& other) const
  {
    return as<HSV>() != other.as<HSV>();
  }
};

}  // namespace colors

namespace utils {

template <typename T>
struct Converter<T, colors::Color> final {
  constexpr static T convert(const colors::Color& color)
  {
    return color.as<T>();
  }
};

}  // namespace utils

}  // namespace gvizard

#endif  // GVIZARD_COLORS_COLOR_HPP_
