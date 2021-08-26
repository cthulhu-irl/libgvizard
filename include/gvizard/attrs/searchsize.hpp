#ifndef GVIZARD_ATTRS_SEARCHSIZE_HPP_
#define GVIZARD_ATTRS_SEARCHSIZE_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct SearchSize final : public AttributeBase<SearchSize, int> {
  using value_type = int;

  constexpr static const char * const name = "searchsize";

  constexpr explicit SearchSize() : AttributeBase() {}
  constexpr explicit SearchSize(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 30; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SEARCHSIZE_HPP_
