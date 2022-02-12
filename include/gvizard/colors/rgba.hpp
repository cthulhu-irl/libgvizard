#ifndef GVIZARD_COLORS_RGBA_HPP_
#define GVIZARD_COLORS_RGBA_HPP_

#include <cstdint>
#include <optional>

namespace gviz::colors {

struct RGBA {
  using octet_t = uint8_t;

  octet_t r = 0;
  octet_t g = 0;
  octet_t b = 0;
  octet_t a = 255;

  constexpr RGBA(octet_t red, octet_t green, octet_t blue,
                 octet_t alpha = 255) noexcept
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha)
  {}

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
      octet_t((value >> 16) & 0xff),
      octet_t((value >>  8) & 0xff),
      octet_t((value >>  0) & 0xff),
      octet_t((value >> 24) & 0xff) // alpha
    };
  }

  constexpr uint32_t to_binary() const noexcept
  {
    return (a << 24) |
           (r << 16) |
           (g <<  8) |
           (b <<  0);
  }

  constexpr bool operator==(const RGBA& other) const noexcept
  {
    return r == other.r && g == other.g && b == other.b && a == other.a;
  }

  constexpr bool operator!=(const RGBA& other) const noexcept
  {
    return r != other.r || g != other.g || b != other.b || a != other.a;
  }
};

}  // namespace gviz::colors

#endif  // GVIZARD_COLORS_RGBA_HPP_
