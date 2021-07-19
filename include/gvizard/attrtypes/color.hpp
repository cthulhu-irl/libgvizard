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

  static std::optional<RGB>
  make(octet_t red, octet_t green, octet_t blue) noexcept
  {
    return RGB{ red, green, blue };
  }

  octet_t min() const noexcept
  {
    return (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
  }

  octet_t max() const noexcept
  {
    return (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
  }

  uint32_t to_binary() const noexcept
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

  static std::optional<RGBA>
  make(octet_t red, octet_t green, octet_t blue) noexcept
  {
    return RGBA{ red, green, blue };
  }

  static std::optional<RGBA>
  make(octet_t red, octet_t green, octet_t blue, octet_t alpha) noexcept
  {
    return RGBA{ red, green, blue, alpha };
  }

  octet_t min() const noexcept
  {
    return (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
  }

  octet_t max() const noexcept
  {
    return (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
  }

  uint32_t to_binary() const noexcept
  {
    return (r << 24) |
           (g << 16) |
           (b <<  8) |
           (a <<  0);
  }
};

struct HSV {
  using octet_t = double;

  HSV(octet_t hue, octet_t saturation, octet_t value)
    : h(hue), s(saturation), v(value)
  {
    if (h < 0.0 || 1.0 < h)
      detail::invalid_argument("hue must be within (0, 1) range");

    if (s < 0.0 || 1.0 < s)
      detail::invalid_argument("saturation must be within (0, 1) range");

    if (v < 0.0 || 1.0 < v)
      detail::invalid_argument("value must be within (0, 1) range");
  }

  static std::optional<HSV> make(octet_t h, octet_t s, octet_t v) noexcept
  {
    if (h < 0.0 || 1.0 < h) return std::nullopt;
    if (s < 0.0 || 1.0 < s) return std::nullopt;
    if (v < 0.0 || 1.0 < v) return std::nullopt;

    HSV hsv{};

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;

    return hsv;
  }

  octet_t hue() const noexcept { return h; }
  octet_t saturation() const noexcept { return s; }
  octet_t value() const noexcept { return v; }

 private:
  HSV() noexcept {}

  octet_t h;
  octet_t s;
  octet_t v;
};

namespace color_convert {
  namespace detail {
    static const HSV hsv_zero_default{0.0, 0.0, 0.0};
  }

  template <typename From, typename To>
  inline To convert(const From&) noexcept
  {
    static_assert(sizeof(From) == 0,
        "given color types for color conversion are not supported.");
  }

  template <>
  inline HSV
  convert<RGB, HSV>(const RGB& rgb) noexcept
  {
    uint8_t min = rgb.min(), max = rgb.max();

    if (max == 0)
      return detail::hsv_zero_default;

    double v = double(max) / 255;

    double s = long(max - min) / max;
    if (s == 0.0)
      return detail::hsv_zero_default;

    // NOTE this will underflow if b > g, but won't be negative,
    //      not sure if abs would be better.
    uint8_t gb_diff = rgb.g - rgb.b;

    double h;
    if (max == rgb.r)
      h = double(  0 + 43 * gb_diff / (max - min)) / 255;

    else if (max == rgb.g)
      h = double( 83 + 43 * gb_diff / (max - min)) / 255;

    else // max == rgb.b
      h = double(171 + 43 * gb_diff / (max - min)) / 255;

    return HSV::make(h, s, v).value();
  }

  template <>
  inline RGB
  convert<HSV, RGB>(const HSV& hsv) noexcept
  {
    if (hsv.saturation() == 0.0)
      return RGB{0, 0, 0};

    uint8_t h = hsv.hue() * 255;
    uint8_t s = hsv.saturation() * 255;
    uint8_t v = hsv.value() * 255;

    uint8_t region, remainder, p, q, t;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

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
  inline RGBA
  convert<RGB, RGBA>(const RGB& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  inline RGB
  convert<RGBA, RGB>(const RGBA& color) noexcept
  {
    return { color.r, color.g, color.b };
  }

  template <>
  inline HSV
  convert<RGBA, HSV>(const RGBA& color) noexcept
  {
    return convert<RGB, HSV>( convert<RGBA, RGB>(color) );
  }

  template <>
  inline RGBA
  convert<HSV, RGBA>(const HSV& color) noexcept
  {
    return convert<RGB, RGBA>( convert<HSV, RGB>(color) );
  }

  // std::is_same_v<From, To> == true
  template <>
  inline RGB
  convert<RGB, RGB>(const RGB& color) noexcept { return color; }

  template <>
  inline RGBA
  convert<RGBA, RGBA>(const RGBA& color) noexcept { return color; }

  template <>
  inline HSV
  convert<HSV, HSV>(const HSV& color) noexcept { return color; }

  template <typename To>
  struct visitor final {
    To operator()(const HSV& color) const
    { return convert<HSV, To>(color); }

    To operator()(const RGB& color) const
    { return convert<RGB, To>(color); }

    To operator()(const RGBA& color) const
    { return convert<RGBA, To>(color); }
  };
}  // namespace color_convert

struct Color {
  using color_variant_t = std::variant<RGB, RGBA, HSV>;

  color_variant_t color;

  Color(const color_variant_t& clr) : color(clr) {}
  Color(color_variant_t&& clr) : color(std::move(clr)) {}

  Color(RGB clr) : color(std::move(clr)) {}
  Color(RGBA clr) : color(std::move(clr)) {}
  Color(HSV clr) : color(std::move(clr)) {}

  static std::optional<Color>
  make_rgb(RGB::octet_t r, RGB::octet_t g, RGB::octet_t b) noexcept
  {
    return Color{ RGB{ r, g, b } };
  }

  static std::optional<Color>
  make_rgba(
    RGBA::octet_t r,
    RGBA::octet_t g,
    RGBA::octet_t b,
    RGBA::octet_t a) noexcept
  {
    return Color{ RGBA{ r, g, b, a } };
  }

  static std::optional<Color>
  make_hsv(HSV::octet_t h, HSV::octet_t s, HSV::octet_t v) noexcept
  {
    auto hsv = HSV::make(h, s, v);
    if (!hsv.has_value())
      return std::nullopt;

    return Color{ hsv.value() };
  }

  template <typename T>
  T as() const noexcept
  {
    return std::visit(color_convert::visitor<T>{}, color);
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
