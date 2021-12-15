#ifndef GVIZARD_ATTRS_SHADOWBOXES_HPP_
#define GVIZARD_ATTRS_SHADOWBOXES_HPP_

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct ShadowBoxes final : public AttributeBase<ShadowBoxes, int> {
  using value_type = int;

  constexpr static const char * const name = "shadowboxes";

  constexpr explicit ShadowBoxes() noexcept : AttributeBase() {}
  constexpr explicit ShadowBoxes(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SHADOWBOXES_HPP_
