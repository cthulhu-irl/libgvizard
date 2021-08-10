#ifndef GVIZARD_ATTRS_AREA_HPP_
#define GVIZARD_ATTRS_AREA_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Area : public AttributeBase<Area, double> {
  using value_type = double;

  constexpr static const char * const name = "area";

  Area() : AttributeBase(get_default_value()) {}
  Area(value_type value) : AttributeBase(value) {}

  constexpr static bool constraint(value_type value) { return value > 0; }

  constexpr static value_type get_default_value() { return 1.0; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_AREA_HPP_
