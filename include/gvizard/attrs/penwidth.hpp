#ifndef GVIZARD_ATTRS_PENWIDTH_HPP_
#define GVIZARD_ATTRS_PENWIDTH_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct PenWidth final : public AttributeBase<PenWidth, double> {
  using value_type = double;

  constexpr static const char * const name = "penwidth";

  constexpr explicit PenWidth() noexcept : AttributeBase() {}
  constexpr explicit PenWidth(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 1.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_PENWIDTH_HPP_
