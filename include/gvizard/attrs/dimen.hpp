#ifndef GVIZARD_ATTRS_DIMEN_HPP_
#define GVIZARD_ATTRS_DIMEN_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Dimen final : public AttributeBase<Dimen, int> {
  using value_type = int;

  constexpr static const char * const name = "dim";

  constexpr explicit Dimen() : AttributeBase(get_default_value()) {}
  constexpr explicit Dimen(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 2;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return 10 >= value && value >= 2;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DIMEN_HPP_
