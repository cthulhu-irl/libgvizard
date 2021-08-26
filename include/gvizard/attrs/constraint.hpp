#ifndef GVIZARD_ATTRS_CONSTRAINT_HPP_
#define GVIZARD_ATTRS_CONSTRAINT_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Constraint final : public AttributeBase<Constraint, bool> {
  using value_type = bool;

  constexpr static const char * const name = "constraint";

  constexpr explicit Constraint() : AttributeBase() {}
  constexpr explicit Constraint(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return true; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CONSTRAINT_HPP_
