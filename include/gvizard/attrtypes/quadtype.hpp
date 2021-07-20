#ifndef GVIZARD_ATTRTYPES_QUADTYPE_HPP_
#define GVIZARD_ATTRTYPES_QUADTYPE_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class QuadType : uint8_t {
  none = 0,
  normal,
  fast
};

constexpr inline QuadType quadtype_from_bool(bool type)
{
  return type ? QuadType::normal : QuadType::none;
}

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_QUADTYPE_HPP_
