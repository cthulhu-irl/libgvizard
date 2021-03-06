#ifndef GVIZARD_ATTRTYPES_STARTTYPE_HPP_
#define GVIZARD_ATTRTYPES_STARTTYPE_HPP_

#include <cstdint>

namespace gviz::attrtypes {

enum class StartTypeStyle : uint8_t {
  none = 0,
  regular,
  self,
  random
};

struct StartType final {
  StartTypeStyle style = StartTypeStyle::none;
  std::size_t    seed  = 0;

  constexpr StartType(StartTypeStyle style = StartTypeStyle::none, std::size_t seed = 0)
    : style(style)
    , seed(seed)
  {}

  constexpr bool operator==(StartType other) const
  {
    return style == other.style && seed == other.seed;
  }

  constexpr bool operator!=(StartType other) const
  {
    return style != other.style || seed != other.seed;
  }
};

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_STARTTYPE_HPP_
