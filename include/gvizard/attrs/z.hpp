#ifndef GVIZARD_ATTRS_Z_HPP_
#define GVIZARD_ATTRS_Z_HPP_

#include <limits>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct ZCoord final : public AttributeBase<ZCoord, double> {
  using value_type = double;

  constexpr static const char * const name = "z";

  constexpr explicit ZCoord() noexcept : AttributeBase() {}
  constexpr explicit ZCoord(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return std::numeric_limits<double>::min();
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_Z_HPP_
