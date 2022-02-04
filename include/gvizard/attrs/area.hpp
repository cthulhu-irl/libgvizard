#ifndef GVIZARD_ATTRS_AREA_HPP_
#define GVIZARD_ATTRS_AREA_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Area final : public AttributeBase<Area, double> {
  using value_type = double;

  constexpr static const char * const name = "area";

  constexpr explicit Area() noexcept : AttributeBase() {}
  constexpr explicit Area(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 1.0;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == 1.0;
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value > 0;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_AREA_HPP_
