#ifndef GVIZARD_ATTRTYPES_PORTPOS_HPP_
#define GVIZARD_ATTRTYPES_PORTPOS_HPP_

#include <cstdint>
#include <string>
#include <optional>

namespace gviz::attrtypes {

enum class CompassPoint : uint8_t {
  _default = 0,
  center,
  north,
  south,
  west,
  east,
  north_east,
  north_west,
  south_east,
  south_west,
};

template <typename StrT = std::string>
struct PortPos final {
  using str_type = StrT;

  std::optional<str_type> port = std::nullopt;
  CompassPoint compass = CompassPoint::_default;

  constexpr bool operator==(const PortPos& other) const
  {
    return compass == other.compass && port == other.port;
  }

  constexpr bool operator!=(const PortPos& other) const
  {
    return compass != other.compass || port != other.port;
  }
};

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_PORTPOS_HPP_
