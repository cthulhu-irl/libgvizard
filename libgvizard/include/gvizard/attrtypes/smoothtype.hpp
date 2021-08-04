#ifndef GVIZARD_ATTRTYPES_SMOOTHTYPE_HPP_
#define GVIZARD_ATTRTYPES_SMOOTHTYPE_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class SmoothType : uint8_t {
  none = 0,
  avg_dist,
  graph_dist,
  power_dist,
  rng,
  spring,
  triangle
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_SMOOTHTYPE_HPP_
