#ifndef GVIZARD_ATTRTYPES_QUADTYPE_HPP_
#define GVIZARD_ATTRTYPES_QUADTYPE_HPP_

#include <cstdint>

#include <gvizard/utils.hpp>

namespace gvizard {
namespace attrtypes {

enum class QuadType : uint8_t {
  none = 0,
  normal,
  fast
};

constexpr inline QuadType quadtype_from_bool(bool type)
{
  return type ? QuadType::normal : QuadType::none;
}

}  // namespace attrtypes

namespace utils {

template <>
struct Converter<attrtypes::QuadType, bool> final {
  constexpr static attrtypes::QuadType convert(bool qtype)
  {
    return attrtypes::quadtype_from_bool(qtype);
  }
};

template <>
struct Converter<bool, attrtypes::QuadType> final {
  constexpr static bool convert(attrtypes::QuadType qtype)
  {
    return qtype == attrtypes::QuadType::normal;
  }
};

}  // namespace utils

}  // namespace gvizard

#endif  // GVIZARD_ATTRTYPES_QUADTYPE_HPP_
