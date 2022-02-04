#ifndef GVIZARD_ATTRS_LEN_HPP_
#define GVIZARD_ATTRS_LEN_HPP_

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Len final : public AttributeBase<Len, double> {
  using value_type = double;

  constexpr static const char * const name = "len";

  constexpr explicit Len() noexcept : AttributeBase() {}
  constexpr explicit Len(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 1.0; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_LEN_HPP_
