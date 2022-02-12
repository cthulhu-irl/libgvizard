#ifndef GVIZARD_COLORS_COLOR_HPP_
#define GVIZARD_COLORS_COLOR_HPP_

#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"
#include "gvizard/colors/x11.hpp"
#include "gvizard/colors/svg.hpp"

#include "gvizard/colors/general.hpp"
#include "gvizard/colors/converter.hpp"

#include "gvizard/utils.hpp"

namespace gviz {
namespace colors {

namespace detail {

template <typename To>
struct color_converter_visitor {
  template <typename From>
  constexpr To operator()(const From& color)
  {
    return ::gviz::utils::Converter<From, To>::convert(color);
  }
};

}  // namespace detail

struct Color {
  using color_variant_t =
    std::variant<
      RGB, RGBA, HSV, X11Color, SVGColor, X11ColorEnum, SVGColorEnum,
      SchemeColor<RGB>, SchemeColor<RGBA>, SchemeColor<HSV>,
      SchemeColor<X11Color>, SchemeColor<SVGColor>,
      SchemeColor<X11ColorEnum>, SchemeColor<SVGColorEnum>
    >;

  color_variant_t color;

  constexpr Color(RGB clr)  : color(std::move(clr)) {}
  constexpr Color(RGBA clr) : color(std::move(clr)) {}
  constexpr Color(HSV clr)  : color(std::move(clr)) {}

  constexpr Color(SVGColorEnum clr)  : color(SVGColor(clr)) {}
  constexpr Color(X11ColorEnum clr)  : color(X11Color(clr)) {}

  constexpr Color(const SVGColor& clr) : color(clr) {}
  constexpr Color(SVGColor&& clr) : color(std::move(clr)) {}

  constexpr Color(const X11Color& clr) : color(clr) {}
  constexpr Color(X11Color&& clr) : color(std::move(clr)) {}

  template <typename ColorT>
  constexpr Color(const SchemeColor<ColorT>& clr) : color(clr) {}

  template <typename ColorT>
  constexpr Color(SchemeColor<ColorT>&& clr) : color(std::move(clr)) {}

  constexpr Color(const color_variant_t& clr) : color(clr) {}
  constexpr Color(color_variant_t&& clr) : color(std::move(clr)) {}

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
    return std::visit(detail::color_converter_visitor<T>{}, color);
  }

  constexpr bool operator==(const Color& other) const
  {
    return as<RGBA>() == other.as<RGBA>();
  }

  constexpr bool operator!=(const Color& other) const
  {
    return as<RGBA>() != other.as<RGBA>();
  }
};

}  // namespace colors

namespace utils {

template <typename To>
struct Converter<colors::Color, To,
                 std::enable_if_t<!std::is_same_v<colors::Color, To>>> final
{
  constexpr static auto convert(const colors::Color& color) -> To
  {
    return color.as<To>();
  }
};

}  // namespace utils

}  // namespace gviz

#endif  // GVIZARD_COLORS_COLOR_HPP_
