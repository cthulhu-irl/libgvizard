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

namespace gvizard::colors {

struct Color {
  using list_type = std::vector<std::tuple<Color, double>>;

  using color_variant_t =
    std::variant<
      RGB, RGBA, HSV,
      SchemeColor<RGB>, SchemeColor<RGBA>, SchemeColor<HSV>
    >;

  color_variant_t color;

  constexpr Color(const color_variant_t& clr) : color(clr) {}

  constexpr Color(const RGB& clr) : color(clr) {}
  constexpr Color(const RGBA& clr) : color(clr) {}
  constexpr Color(const HSV& clr) : color(clr) {}

  constexpr Color(const SchemeColor<RGB>& clr) : color(clr) {}
  constexpr Color(const SchemeColor<RGBA>& clr) : color(clr) {}
  constexpr Color(const SchemeColor<HSV>& clr) : color(clr) {}

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
    return std::visit(color_convert::visitor<T>{}, color);
  }
};

}  // namespace gvizard::colors

#endif  // GVIZARD_COLORS_COLOR_HPP_