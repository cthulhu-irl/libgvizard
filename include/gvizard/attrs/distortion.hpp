#ifndef GVIZARD_ATTRS_DISTORTION_HPP_
#define GVIZARD_ATTRS_DISTORTION_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Distortion final : public AttributeBase<Distortion, double> {
  using value_type = double;

  constexpr static const char * const name = "distortion";

  constexpr explicit Distortion() noexcept : AttributeBase() {}
  constexpr explicit Distortion(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 0.0;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= -100.0;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_DISTORTION_HPP_
