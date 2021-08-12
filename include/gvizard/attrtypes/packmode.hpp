#ifndef GVIZARD_ATTRTYPES_PACKMODE_HPP_
#define GVIZARD_ATTRTYPES_PACKMODE_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class PackModeEnum : uint8_t {
  node = 0,
  clust,
  graph,
  array
};

enum class PackModeArrayFlag : uint8_t {
  none = 0,
  column,
  user,
  top,
  bottom,
  left,
  right
};

struct PackMode final {
  PackModeEnum mode = PackModeEnum::node;
  PackModeArrayFlag flag = PackModeArrayFlag::none;
  std::size_t number = 0;

  constexpr PackMode& normalize() noexcept
  {
    if (mode != PackModeEnum::array) {
      flag = PackModeArrayFlag::none;
      number = 0;
    }

    return *this;
  }

  constexpr PackMode normalized() const noexcept
  {
    return (mode == PackModeEnum::array) ? *this : PackMode{ mode };
  }

  constexpr bool operator==(PackMode other) const
  {
    return mode == other.mode && flag == other.flag;
  }

  constexpr bool operator!=(PackMode other) const
  {
    return mode != other.mode || flag != other.flag;
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_PACKMODE_HPP_
