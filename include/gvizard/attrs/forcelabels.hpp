#ifndef GVIZARD_ATTRS_FORCELABELS_HPP_
#define GVIZARD_ATTRS_FORCELABELS_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct ForceLabels final : public AttributeBase<ForceLabels, bool> {
  using value_type = bool;

  constexpr static const char * const name = "forcelabels";

  constexpr explicit ForceLabels() noexcept : AttributeBase() {}
  constexpr explicit ForceLabels(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return true; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_FORCELABELS_HPP_
