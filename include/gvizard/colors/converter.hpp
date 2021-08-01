#ifndef GVIZARD_COLORS_CONVERTER_HPP_
#define GVIZARD_COLORS_CONVERTER_HPP_

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"

#include "gvizard/colors/general.hpp"

namespace gvizard::colors {

namespace color_convert {
  namespace detail {
    constexpr inline const HSV hsv_zero_default{0., 0., 0.};
  }

  template <typename To, typename From>
  constexpr inline To convert(const From&) noexcept
  {
    static_assert(sizeof(From) == 0,
        "given color types for color conversion are not supported.");
  }

  template <>
  constexpr inline HSV
  convert<HSV, RGB>(const RGB& rgb) noexcept
  {
    uint8_t min = rgb.min(), max = rgb.max();

    if (max == 0)
      return detail::hsv_zero_default;

    double v = double(max) / 255;

    double s = long(max - min) / max;
    if (s == 0.)
      return detail::hsv_zero_default;

    // NOTE this will underflow if b > g, but won't be negative,
    //      not sure if abs would be better.
    uint8_t gb_diff = rgb.g - rgb.b;

    double h = 0;
    if (max == rgb.r)
      h = double(  0 + 43 * gb_diff / (max - min)) / 255.;

    else if (max == rgb.g)
      h = double( 83 + 43 * gb_diff / (max - min)) / 255.;

    else // max == rgb.b
      h = double(171 + 43 * gb_diff / (max - min)) / 255.;

    return HSV::make(h, s, v).value();
  }

  template <>
  constexpr inline RGB
  convert<RGB, HSV>(const HSV& hsv) noexcept
  {
    if (hsv.saturation() == 0.)
      return RGB{0, 0, 0};

    uint8_t h = hsv.hue() * 255;
    uint8_t s = hsv.saturation() * 255;
    uint8_t v = hsv.value() * 255;

    uint8_t region = h / 43;
    uint8_t remainder = (h - (region * 43)) * 6;

    uint8_t p = (v * (255 - s)) >> 8;
    uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
      case 0:  return RGB{ v, t, p };
      case 1:  return RGB{ q, v, p };
      case 2:  return RGB{ p, v, t };
      case 3:  return RGB{ p, q, v };
      case 4:  return RGB{ t, p, v };
      default: return RGB{ v, p, q };
    }
  }

  template <>
  constexpr inline RGBA
  convert<RGBA, RGB>(const RGB& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  constexpr inline RGB
  convert<RGB, RGBA>(const RGBA& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  constexpr inline HSV
  convert<HSV, RGBA>(const RGBA& color) noexcept
  {
    return convert<HSV, RGB>( convert<RGB, RGBA>(color) );
  }

  template <>
  constexpr inline RGBA
  convert<RGBA, HSV>(const HSV& color) noexcept
  {
    return convert<RGBA, RGB>( convert<RGB, HSV>(color) );
  }

  // std::is_same_v<From, To> == true
  template <>
  constexpr inline RGB
  convert<RGB, RGB>(const RGB& color) noexcept { return color; }

  template <>
  constexpr inline RGBA
  convert<RGBA, RGBA>(const RGBA& color) noexcept { return color; }

  template <>
  constexpr inline HSV
  convert<HSV, HSV>(const HSV& color) noexcept { return color; }

  template <typename To>
  struct visitor final {
    constexpr To operator()(const HSV& color) const
    { return convert<To, HSV>(color); }

    constexpr To operator()(const RGB& color) const
    { return convert<To, RGB>(color); }

    constexpr To operator()(const RGBA& color) const
    { return convert<To, RGBA>(color); }

    template <typename From>
    constexpr To operator()(const SchemeColor<From>& color) const
    { return convert<To, From>(color.color); }
  };
}  // namespace color_convert

}  // namespace gvizard::colors

#endif  // GVIZARD_COLORS_CONVERTER_HPP_
