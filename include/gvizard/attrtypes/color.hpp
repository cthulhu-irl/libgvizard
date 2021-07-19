#ifndef GVIZARD_ATTRTYPES_COLOR_HPP_
#define GVIZARD_ATTRTYPES_COLOR_HPP_

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <variant>

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
  HSV() noexcept {}

  octet_t h;
  octet_t s;
  octet_t v;
};

namespace color_convert {
  namespace detail {
    constexpr inline const HSV hsv_zero_default{0., 0., 0.};
  }

  template <typename From, typename To>
  constexpr inline To convert(const From&) noexcept
  {
    static_assert(sizeof(From) == 0,
        "given color types for color conversion are not supported.");
  }

  template <>
  constexpr inline HSV
  convert<RGB, HSV>(const RGB& rgb) noexcept
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
  convert<HSV, RGB>(const HSV& hsv) noexcept
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
  convert<RGB, RGBA>(const RGB& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  constexpr inline RGB
  convert<RGBA, RGB>(const RGBA& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  constexpr inline HSV
  convert<RGBA, HSV>(const RGBA& color) noexcept
  {
    return convert<RGB, HSV>( convert<RGBA, RGB>(color) );
  }

  template <>
  constexpr inline RGBA
  convert<HSV, RGBA>(const HSV& color) noexcept
  {
    return convert<RGB, RGBA>( convert<HSV, RGB>(color) );
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
    { return convert<HSV, To>(color); }

    constexpr To operator()(const RGB& color) const
    { return convert<RGB, To>(color); }

    constexpr To operator()(const RGBA& color) const
    { return convert<RGBA, To>(color); }
  };
}  // namespace color_convert

struct Color {
  using color_variant_t = std::variant<RGB, RGBA, HSV>;

  color_variant_t color;

  constexpr Color(const color_variant_t& clr) : color(clr) {}
  constexpr Color(color_variant_t&& clr) : color(std::move(clr)) {}

  constexpr Color(RGB clr) : color(std::move(clr)) {}
  constexpr Color(RGBA clr) : color(std::move(clr)) {}
  constexpr Color(HSV clr) : color(std::move(clr)) {}

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

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
