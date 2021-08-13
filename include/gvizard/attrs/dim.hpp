#ifndef GVIZARD_ATTRS_DIM_HPP_
#define GVIZARD_ATTRS_DIM_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Dim final : public AttributeBase<Dim, int> {
  using value_type = int;

  constexpr static const char * const name = "dim";

  constexpr explicit Dim() : AttributeBase(get_default_value()) {}
  constexpr explicit Dim(value_type value) : AttributeBase(value) {}

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
    return value >= get_default_value();
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DIM_HPP_
