#ifndef GVIZARD_ATTRS_MINLEN_HPP_
#define GVIZARD_ATTRS_MINLEN_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct MinLen final : public AttributeBase<MinLen, int> {
  using value_type = int;

  constexpr static const char * const name = "minlen";

  constexpr explicit MinLen() noexcept : AttributeBase() {}
  constexpr explicit MinLen(value_type value) : AttributeBase(value) {}

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

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_MINLEN_HPP_
