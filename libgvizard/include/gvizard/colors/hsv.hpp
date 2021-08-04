#ifndef GVIZARD_COLORS_HSV_HPP_
#define GVIZARD_COLORS_HSV_HPP_

#include <stdexcept>
#include <optional>

namespace gvizard::detail::hsv {
  [[noreturn]] inline void invalid_argument(const char *reason)
  {
    throw std::invalid_argument(reason);
  }
}

namespace gvizard::colors {

struct HSV {
  using octet_t = double;

  constexpr HSV(octet_t hue, octet_t saturation, octet_t value)
    : h(hue), s(saturation), v(value)
  {
    if (h < 0. || 1. < h)
      detail::hsv::invalid_argument("hue must be within (0, 1) range");

    if (s < 0. || 1. < s)
      detail::hsv::invalid_argument("saturation must be within (0, 1) range");

    if (v < 0. || 1. < v)
      detail::hsv::invalid_argument("value must be within (0, 1) range");
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

}  // namespace gvizard::colors

#endif  // GVIZARD_COLORS_HSV_HPP_
