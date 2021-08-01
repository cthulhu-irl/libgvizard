#ifndef GVIZARD_COLORS_CONVERTER_HPP_
#define GVIZARD_COLORS_CONVERTER_HPP_

#include "gvizard/utils.hpp"

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"

#include "gvizard/colors/general.hpp"

using gvizard::colors::HSV;
using gvizard::colors::RGB;
using gvizard::colors::RGBA;
using gvizard::colors::SchemeColor;

namespace gvizard {
namespace utils {

constexpr static inline const HSV hsv_zero_default{0., 0., 0.};

template <>
struct Converter<HSV, RGB> final {
  constexpr static HSV convert(const RGB& rgb) noexcept
  {
    uint8_t min = rgb.min(), max = rgb.max();

    if (max == 0)
      return hsv_zero_default;

    double v = double(max) / 255;

    double s = long(max - min) / max;
    if (s == 0.)
      return hsv_zero_default;

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
};

template <>
struct Converter<RGB, HSV> final {
  constexpr static RGB convert(const HSV& hsv) noexcept
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
};

template <>
struct Converter<RGBA, RGB> final {
  constexpr static RGBA convert(const RGB& color) noexcept
  {
    return { color.r, color.g, color.b };
  }
};

template <>
struct Converter<RGB, RGBA> final {
  constexpr static RGB convert(const RGBA& color) noexcept
  {
    return RGB{ color.r, color.g, color.b };
  }
};

template <>
struct Converter<HSV, RGBA> final {
  constexpr static HSV convert(const RGBA& color) noexcept
  {
    return Converter<HSV, RGB>::convert(
        Converter<RGB, RGBA>::convert(color)
    );
  }
};

template <>
struct Converter<RGBA, HSV> final {
  constexpr static RGBA convert(const HSV& color) noexcept
  {
    return Converter<RGBA, RGB>::convert(
        Converter<RGB, HSV>::convert(color)
    );
  }
};

}  // namespace utils

namespace colors {

template <typename To, typename From>
using Converter = gvizard::utils::Converter<To, From>;

template <typename To>
struct ColorConverterCallable final {
  constexpr To operator()(const HSV& color) const
  {
    return Converter<To, HSV>::convert(color);
  }

  constexpr To operator()(const RGB& color) const
  {
    return Converter<To, RGB>::convert(color);
  }

  constexpr To operator()(const RGBA& color) const
  {
    return Converter<To, RGBA>::convert(color);
  }

  template <typename From>
  constexpr To operator()(const SchemeColor<From>& color) const
  {
    return Converter<To, From>::convert(color.color);
  }
};

}  // namespace colors
}  // namespace gvizard

#endif  // GVIZARD_COLORS_CONVERTER_HPP_
