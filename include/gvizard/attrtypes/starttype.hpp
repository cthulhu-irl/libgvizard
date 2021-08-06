#ifndef GVIZARD_ATTRTYPES_STARTTYPE_HPP_
#define GVIZARD_ATTRTYPES_STARTTYPE_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class StartTypeStyle : uint8_t {
  none = 0,
  regular,
  self,
  random
};

struct StartType final {
  StartTypeStyle style = StartTypeStyle::none;
  std::size_t seed = 0;
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_STARTTYPE_HPP_
