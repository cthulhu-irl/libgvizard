#ifndef GVIZARD_COLORS_CONVERTER_HPP_
#define GVIZARD_COLORS_CONVERTER_HPP_

#include "gvizard/utils.hpp"

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"
#include "gvizard/colors/x11.hpp"
#include "gvizard/colors/svg.hpp"

#include "gvizard/colors/general.hpp"

using gviz::colors::HSV;
using gviz::colors::RGB;
using gviz::colors::RGBA;
using gviz::colors::X11Color;
using gviz::colors::SVGColor;
using gviz::colors::X11ColorEnum;
using gviz::colors::SVGColorEnum;
using gviz::colors::SchemeColor;

constexpr static inline const HSV hsv_zero_default{0., 0., 0.};

namespace gviz {
namespace utils {

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
    return RGBA{ color.r, color.g, color.b };
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

template <typename T, typename U>
struct Converter<SchemeColor<T>, SchemeColor<U>> final {
  constexpr static SchemeColor<T> convert(const SchemeColor<U>& color)
  {
    return SchemeColor<T>{
      color.name,
      Converter<T, U>::convert(color.color),
      color.scheme
    };
  }
};

template <typename T, typename U>
struct Converter<T, SchemeColor<U>> final {
  constexpr static T convert(const SchemeColor<U>& color)
  {
    return Converter<T, U>::convert(color.color);
  }
};

template <typename To>
struct Converter<To, X11Color> final {
  constexpr static To convert(const X11Color& color)
  {
    return Converter<To, RGB>::convert(color.get_color());
  }
};

template <typename To>
struct Converter<To, SVGColor> final {
  constexpr static To convert(const SVGColor& color)
  {
    return Converter<To, RGB>::convert(color.get_color());
  }
};

template <typename To>
struct Converter<To, X11ColorEnum> final {
  constexpr static To convert(X11ColorEnum color)
  {
    return Converter<To, RGB>::convert(X11Color::list[uint16_t(color)].color);
  }
};

template <typename To>
struct Converter<To, SVGColorEnum> final {
  constexpr static To convert(SVGColorEnum color)
  {
    return Converter<To, RGB>::convert(X11Color::list[uint16_t(color)].color);
  }
};

template <typename T>
struct Converter<SchemeColor<T>, X11ColorEnum> final {
  constexpr static SchemeColor<T> convert(X11ColorEnum color)
  {
    const SchemeColor<RGB> scheme_color = X11Color::list[uint16_t(color)];
    return SchemeColor<T>{
      scheme_color.name,
      Converter<T, RGB>::convert(scheme_color.color),
      scheme_color.scheme
    };
  }
};

template <typename T>
struct Converter<SchemeColor<T>, SVGColorEnum> final {
  constexpr static SchemeColor<T> convert(SVGColorEnum color)
  {
    const SchemeColor<RGB> scheme_color = SVGColor::list[uint16_t(color)];
    return SchemeColor<T>{
      scheme_color.name,
      Converter<T, RGB>::convert(scheme_color.color),
      scheme_color.scheme
    };
  }
};

template <>
struct Converter<X11Color, SVGColorEnum> final {
  constexpr static X11Color convert(X11ColorEnum color) noexcept
  {
    return X11Color(color);
  }
};

template <>
struct Converter<SVGColor, SVGColorEnum> final {
  constexpr static SVGColor convert(SVGColorEnum color) noexcept
  {
    return SVGColor(color);
  }
};

template <>
struct Converter<X11ColorEnum, X11Color> final {
  constexpr static X11ColorEnum convert(const X11Color& color) noexcept
  {
    return color.get_enum();
  }
};

template <>
struct Converter<SVGColorEnum, SVGColor> final {
  constexpr static SVGColorEnum convert(const SVGColor& color) noexcept
  {
    return color.get_enum();
  }
};

}  // namespace utils

namespace colors {

using gviz::utils::Converter;

template <typename To>
struct ColorConverterCallable final {
  template <typename From>
  constexpr To operator()(const From& color) const
  {
    return Converter<To, From>::convert(color);
  }
};

}  // namespace colors
}  // namespace gviz

#endif  // GVIZARD_COLORS_CONVERTER_HPP_
