#ifndef GVIZARD_COLORS_CONVERTER_HPP_
#define GVIZARD_COLORS_CONVERTER_HPP_

#include <cstdint>
#include <type_traits>

#include "gvizard/utils.hpp"

#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/rgba.hpp"
#include "gvizard/colors/hsv.hpp"
#include "gvizard/colors/x11.hpp"
#include "gvizard/colors/svg.hpp"

#include "gvizard/colors/general.hpp"

namespace gviz {
namespace utils {

namespace detail {

template <typename T, typename U>
using avoid_same_t = std::enable_if_t<!std::is_same_v<T, U>>;

}  // namespace detail

constexpr static inline const gviz::colors::HSV hsv_zero_default{0., 0., 0.};

template <>
struct Converter<colors::RGB, colors::HSV> final {
  constexpr static auto convert(const colors::RGB& rgb) noexcept
    -> colors::HSV
  {
    uint8_t min = rgb.min();
    uint8_t max = rgb.max();

    if (max == 0)
      return hsv_zero_default;

    double v = double(max) / 255.;

    double s = double(max - min) / max;
    if (s == 0.)
      return hsv_zero_default;

    // NOTE this will underflow if b > g, but won't be negative,
    //      not sure if abs would be better.
    uint8_t gb_diff = rgb.g - rgb.b;

    double h = 0;
    if (max == rgb.r)
      h = double(  0.f + 43.f * gb_diff / (max - min)) / 255.;

    else if (max == rgb.g)
      h = double( 83.f + 43.f * gb_diff / (max - min)) / 255.;

    else // max == rgb.b
      h = double(171.f + 43.f * gb_diff / (max - min)) / 255.;

    return colors::HSV::make(h, s, v).value();
  }
};

template <>
struct Converter<colors::HSV, colors::RGB> final {
  constexpr static auto convert(const colors::HSV& hsv) noexcept
    -> colors::RGB
  {
    if (hsv.saturation() == 0.)
      return colors::RGB{0, 0, 0};

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
      case 0:  return colors::RGB{ v, t, p };
      case 1:  return colors::RGB{ q, v, p };
      case 2:  return colors::RGB{ p, v, t };
      case 3:  return colors::RGB{ p, q, v };
      case 4:  return colors::RGB{ t, p, v };
      default: return colors::RGB{ v, p, q };
    }
  }
};

template <>
struct Converter<colors::RGB, colors::RGBA> final {
  constexpr static auto convert(const colors::RGB& color) noexcept
    -> colors::RGBA
  {
    return colors::RGBA{ color.r, color.g, color.b };
  }
};

template <>
struct Converter<colors::RGBA, colors::RGB> final {
  constexpr static auto convert(const colors::RGBA& color) noexcept
    -> colors::RGB
  {
    return colors::RGB{ color.r, color.g, color.b };
  }
};

template <>
struct Converter<colors::HSV, colors::RGBA> final {
  constexpr static auto convert(const colors::HSV& color) noexcept
    -> colors::RGBA
  {
    return Converter<colors::RGB, colors::RGBA>::convert(
        Converter<colors::HSV, colors::RGB>::convert(color)
    );
  }
};

template <>
struct Converter<colors::RGBA, colors::HSV> final {
  constexpr static auto convert(const colors::RGBA& color) noexcept
    -> colors::HSV
  {
    return Converter<colors::RGB, colors::HSV>::convert(
        Converter<colors::RGBA, colors::RGB>::convert(color)
    );
  }
};

// -- SchemeColor

template <typename T, typename U>
struct Converter<colors::SchemeColor<T>, colors::SchemeColor<U>,
                 detail::avoid_same_t<T, U>> final
{
  constexpr static auto convert(const colors::SchemeColor<T>& color)
    -> colors::SchemeColor<U>
  {
    return colors::SchemeColor<U>{
      color.name,
      Converter<T, U>::convert(color.color),
      color.scheme
    };
  }
};

template <typename T, typename U>
struct Converter<colors::SchemeColor<T>, U,
                 detail::avoid_same_t<colors::SchemeColor<T>, U>> final
{
  constexpr static auto convert(const colors::SchemeColor<T>& color) -> U
  {
    return Converter<T, U>::convert(color.color);
  }
};

// -- SVG and X11 colors

template <typename To>
struct Converter<colors::X11Color, To,
                 detail::avoid_same_t<colors::X11Color, To>> final
{
  constexpr static auto convert(const colors::X11Color& color) -> To
  {
    return Converter<colors::RGB, To>::convert(color.get_color());
  }
};

template <typename To>
struct Converter<colors::SVGColor, To,
                 detail::avoid_same_t<colors::SVGColor, To>> final
{
  constexpr static auto convert(const colors::SVGColor& color) -> To
  {
    return Converter<colors::RGB, To>::convert(color.get_color());
  }
};

// -- SVG and X11 color enums

template <typename To>
struct Converter<colors::X11ColorEnum, To,
                 detail::avoid_same_t<colors::X11ColorEnum, To>> final
{
  constexpr static auto convert(colors::X11ColorEnum color) -> To
  {
    return Converter<colors::RGB, To>::convert(
        colors::X11Color::list[uint16_t(color)].color
    );
  }
};

template <typename To>
struct Converter<colors::SVGColorEnum, To,
                 detail::avoid_same_t<colors::SVGColorEnum, To>> final
{
  constexpr static auto convert(colors::SVGColorEnum color) -> To
  {
    return Converter<colors::RGB, To>::convert(
        colors::SVGColor::list[uint16_t(color)].color
    );
  }
};

template <typename T>
struct Converter<colors::X11ColorEnum, colors::SchemeColor<T>> final {
  constexpr static auto convert(colors::X11ColorEnum color)
    -> colors::SchemeColor<T>
  {
    const colors::SchemeColor<colors::RGB> scheme_color =
        colors::X11Color::list[uint16_t(color)];

    return colors::SchemeColor<T>{
      scheme_color.name,
      Converter<colors::RGB, T>::convert(scheme_color.color),
      scheme_color.scheme
    };
  }
};

template <typename T>
struct Converter<colors::SVGColorEnum, colors::SchemeColor<T>> final {
  constexpr static auto convert(colors::SVGColorEnum color)
    -> colors::SchemeColor<T>
  {
    const colors::SchemeColor<colors::RGB> scheme_color =
        colors::SVGColor::list[uint16_t(color)];

    return colors::SchemeColor<T>{
      scheme_color.name,
      Converter<colors::RGB, T>::convert(scheme_color.color),
      scheme_color.scheme
    };
  }
};

// -- X11 and SVG colors and enums

template <>
struct Converter<colors::X11Color, colors::X11ColorEnum> final {
  constexpr static auto convert(const colors::X11Color& color) noexcept
    -> colors::X11ColorEnum
  {
    return color.get_enum();
  }
};

template <>
struct Converter<colors::SVGColor, colors::SVGColorEnum> final {
  constexpr static auto convert(const colors::SVGColor& color) noexcept
    -> colors::SVGColorEnum
  {
    return color.get_enum();
  }
};

template <>
struct Converter<colors::X11ColorEnum, colors::X11Color> final {
  constexpr static auto convert(colors::X11ColorEnum color) noexcept
    -> colors::X11Color
  {
    return colors::X11Color(color);
  }
};

template <>
struct Converter<colors::SVGColorEnum, colors::SVGColor> final {
  constexpr static auto convert(colors::SVGColorEnum color) noexcept
    -> colors::SVGColor
  {
    return colors::SVGColor(color);
  }
};

}  // namespace utils
}  // namespace gviz

#endif  // GVIZARD_COLORS_CONVERTER_HPP_
