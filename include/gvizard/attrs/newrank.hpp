#ifndef GVIZARD_ATTRS_NEWRANK_HPP_
#define GVIZARD_ATTRS_NEWRANK_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct NewRank final : public AttributeBase<NewRank, bool> {
  using value_type = bool;

  constexpr static const char * const name = "newrank";

  constexpr explicit NewRank() noexcept : AttributeBase() {}
  constexpr explicit NewRank(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_NEWRANK_HPP_
