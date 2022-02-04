#ifndef GVIZARD_ATTRS_COMPOUND_HPP_
#define GVIZARD_ATTRS_COMPOUND_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Compound final : public AttributeBase<Compound, bool> {
  using value_type = bool;

  constexpr static const char * const name = "compound";

  constexpr explicit Compound() noexcept : AttributeBase() {}
  constexpr explicit Compound(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_COMPOUND_HPP_
