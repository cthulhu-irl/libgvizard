#ifndef GVIZARD_ATTRS_PERIPHERIES_HPP_
#define GVIZARD_ATTRS_PERIPHERIES_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Peripheries final : public AttributeBase<Peripheries, int> {
  using value_type = int;

  constexpr static const char * const name = "peripheries";

  constexpr explicit Peripheries() noexcept : AttributeBase() {}
  constexpr explicit Peripheries(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 1; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_PERIPHERIES_HPP_
