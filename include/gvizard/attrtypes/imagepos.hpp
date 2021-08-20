#ifndef GVIZARD_ATTRTYPES_IMAGEPOS_HPP_
#define GVIZARD_ATTRTYPES_IMAGEPOS_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class ImagePosEnum : uint8_t {
  mc = 0, // middle-center
  tl,     // top-left
  tc,     // top-center
  tr,     // top-right
  ml,     // middle-left
  mr,     // middle-right
  bl,     // bottom-left
  bc,     // bottom-center
  br,     // bottom-right
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_IMAGEPOS_HPP_
