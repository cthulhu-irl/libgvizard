#ifndef GVIZARD_ATTRTYPES_RANK_HPP_
#define GVIZARD_ATTRTYPES_RANK_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class RankDir : uint8_t {
  top_bottom = 0,
  bottom_top,
  left_right,
  right_left,
};

enum class RankType : uint8_t {
  none = 0,
  same,
  min,
  max,
  source,
  sink
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_RANK_HPP_
