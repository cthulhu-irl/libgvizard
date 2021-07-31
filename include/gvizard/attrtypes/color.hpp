#ifndef GVIZARD_ATTRTYPES_COLOR_HPP_
#define GVIZARD_ATTRTYPES_COLOR_HPP_

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <variant>
#include <vector>

#include "gvizard/utils.hpp"

namespace gvizard::detail {
  [[noreturn]] inline void invalid_argument(const char *reason)
  {
    throw std::invalid_argument(reason);
  }
}

namespace gvizard::attrtypes {

struct RGB {
  using octet_t = uint8_t;

  octet_t r = 0;
  octet_t g = 0;
  octet_t b = 0;

  constexpr static std::optional<RGB>
  make(octet_t red, octet_t green, octet_t blue) noexcept
  {
    return RGB{ red, green, blue };
  }

  constexpr octet_t min() const noexcept
  {
    return (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
  }

  constexpr octet_t max() const noexcept
  {
    return (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
  }

  constexpr static RGB from_binary(uint32_t value) noexcept
  {
    return RGB{
      octet_t((value >> 16) & 0xff),
      octet_t((value >>  8) & 0xff),
      octet_t((value >>  0) & 0xff)
    };
  }

  constexpr uint32_t to_binary() const noexcept
  {
    return (r << 16) |
           (g <<  8) |
           (b <<  0);
  }
};

struct RGBA {
  using octet_t = uint8_t;

  octet_t r = 0;
  octet_t g = 0;
  octet_t b = 0;
  octet_t a = 255;

  constexpr static std::optional<RGBA>
  make(octet_t red, octet_t green, octet_t blue) noexcept
  {
    return RGBA{ red, green, blue };
  }

  constexpr static std::optional<RGBA>
  make(octet_t red, octet_t green, octet_t blue, octet_t alpha) noexcept
  {
    return RGBA{ red, green, blue, alpha };
  }

  constexpr octet_t min() const noexcept
  {
    return (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
  }

  constexpr octet_t max() const noexcept
  {
    return (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
  }

  constexpr static RGBA from_binary(uint32_t value) noexcept
  {
    return RGBA{
      octet_t((value >> 24) & 0xff),
      octet_t((value >> 16) & 0xff),
      octet_t((value >>  8) & 0xff),
      octet_t((value >>  0) & 0xff)
    };
  }

  constexpr uint32_t to_binary() const noexcept
  {
    return (r << 24) |
           (g << 16) |
           (b <<  8) |
           (a <<  0);
  }
};

struct HSV {
  using octet_t = double;

  constexpr HSV(octet_t hue, octet_t saturation, octet_t value)
    : h(hue), s(saturation), v(value)
  {
    if (h < 0. || 1. < h)
      detail::invalid_argument("hue must be within (0, 1) range");

    if (s < 0. || 1. < s)
      detail::invalid_argument("saturation must be within (0, 1) range");

    if (v < 0. || 1. < v)
      detail::invalid_argument("value must be within (0, 1) range");
  }

  constexpr static std::optional<HSV>
  make(octet_t h, octet_t s, octet_t v) noexcept
  {
    if (h < 0. || 1. < h) return std::nullopt;
    if (s < 0. || 1. < s) return std::nullopt;
    if (v < 0. || 1. < v) return std::nullopt;

    HSV hsv{};

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;

    return hsv;
  }

  constexpr octet_t hue() const noexcept { return h; }
  constexpr octet_t saturation() const noexcept { return s; }
  constexpr octet_t value() const noexcept { return v; }

 private:
  constexpr HSV() noexcept {}

  octet_t h{};
  octet_t s{};
  octet_t v{};
};

template <typename ColorT>
struct NamedColor final {
  using color_type = ColorT;

  const char *name = nullptr;
  color_type  color{};

  constexpr operator color_type() const
    noexcept(noexcept(color_type(color)))
  {
    return color;
  }
};

template <typename ColorT>
class WeightedColor final {
 public:
  using color_type = ColorT;

 private:
  color_type color_;
  double     weight_;

 public:
  constexpr WeightedColor(ColorT color, double weight)
    : color_(color), weight_(weight)
  {
    if (0. > weight_ || weight_ > 1.)
      throw std::invalid_argument("given weight is out of range. (0, 1)");
  }

  constexpr double get_color() const noexcept(noexcept(color_type(color_)))
  {
    return color_;
  }

  constexpr double get_weight() const noexcept { return weight_; }

  constexpr WeightedColor& set_color(const color_type& color)
  {
    color_ = color;
  }

  constexpr WeightedColor& set_weight(double weight)
  {
    if (0. > weight || weight > 1.)
      throw std::invalid_argument("given weight is out of range. (0, 1)");

    weight_ = weight;
  }
};

namespace color_convert {
  // NOTE NamedColor doesn't need convert specialization
  //      as it is implicitly convertible to its inner color_type.

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
    constexpr To operator()(const NamedColor<From>& color) const
    { return convert<To, From>(color.color); }
  };
}  // namespace color_convert

struct Color {
  using list_type = std::vector<std::tuple<Color, double>>;

  using color_variant_t =
    std::variant<
      RGB, RGBA, HSV,
      NamedColor<RGB>, NamedColor<RGBA>, NamedColor<HSV>
    >;

  color_variant_t color;

  constexpr Color(const color_variant_t& clr) : color(clr) {}

  constexpr Color(const RGB& clr) : color(clr) {}
  constexpr Color(const RGBA& clr) : color(clr) {}
  constexpr Color(const HSV& clr) : color(clr) {}

  constexpr Color(const NamedColor<RGB>& clr) : color(clr) {}
  constexpr Color(const NamedColor<RGBA>& clr) : color(clr) {}
  constexpr Color(const NamedColor<HSV>& clr) : color(clr) {}

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

}  // namespace gvizard::attrtypes

namespace gvizard::utils {

template <typename T>
struct Converter<T, attrtypes::Color> {
  constexpr static T
  convert(const attrtypes::Color& color) { return color.as<T>(); }
};

template <typename T>
struct Converter<T, attrtypes::HSV> {
  constexpr static T
  convert(const attrtypes::HSV& hsv)
  { return attrtypes::color_convert::convert<T, attrtypes::HSV>(hsv); }
};

template <typename T>
struct Converter<T, attrtypes::RGBA> {
  constexpr static T
  convert(const attrtypes::RGBA& rgba)
  { return attrtypes::color_convert::convert<T, attrtypes::RGBA>(rgba); }
};

template <typename T>
struct Converter<T, attrtypes::RGB> {
  constexpr static T
  convert(const attrtypes::RGB& rgb)
  { return attrtypes::color_convert::convert<T, attrtypes::RGB>(rgb); }
};

template <typename T, typename U>
struct Converter<T, attrtypes::NamedColor<U>> {
  constexpr static T convert(const attrtypes::NamedColor<U>& clr)
  {
    return
      attrtypes::color_convert::convert<T, attrtypes::NamedColor<U>>(clr);
  }
};

}  // namespace gvizard::utils

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
