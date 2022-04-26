#ifndef GVIZARD_ATTRS_MCLIMIT_HPP_
#define GVIZARD_ATTRS_MCLIMIT_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct MCLimit final : public AttributeBase<MCLimit, double> {
  using value_type = double;

  constexpr static const char * const name = "mclimit";

  constexpr explicit MCLimit() noexcept : AttributeBase() {}
  constexpr explicit MCLimit(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 1.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_MCLIMIT_HPP_
