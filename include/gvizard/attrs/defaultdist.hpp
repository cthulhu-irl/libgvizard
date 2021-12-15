#ifndef GVIZARD_ATTRS_DEFAULTDIST_HPP_
#define GVIZARD_ATTRS_DEFAULTDIST_HPP_

#include <limits>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct DefaultDist final : public AttributeBase<DefaultDist, double> {
  using value_type = double;

  constexpr static const char * const name = "defaultdist";

  constexpr explicit DefaultDist() noexcept : AttributeBase() {}
  constexpr explicit DefaultDist(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 0.; // can't compute this here: 1 + (avg. len) * sqrt(|V|)
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= std::numeric_limits<double>::epsilon();
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DEFAULTDIST_HPP_
