#ifndef GVIZARD_COLORS_RGB_HPP_
#define GVIZARD_COLORS_RGB_HPP_

#include <cstdint>
#include <optional>

#undef RGB  // windows-specific

namespace gviz::colors {

struct RGB {
  using octet_t = uint8_t;

  octet_t r = 0;
  octet_t g = 0;
  octet_t b = 0;

  constexpr RGB(octet_t red, octet_t green, octet_t blue) noexcept
    : r(red)
    , g(green)
    , b(blue)
  {}

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

  constexpr bool operator==(const RGB& other) const noexcept
  {
    return r == other.r && g == other.g && b == other.b;
  }

  constexpr bool operator!=(const RGB& other) const noexcept
  {
    return r != other.r || g != other.g || b != other.b;
  }
};

}  // namespace gviz::colors

#endif  // GVIZARD_COLORS_RGB_HPP_
