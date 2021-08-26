#ifndef GVIZARD_ATTRS_SORTV_HPP_
#define GVIZARD_ATTRS_SORTV_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct SortV final : public AttributeBase<SortV, int> {
  using value_type = int;

  constexpr static const char * const name = "sortv";

  constexpr explicit SortV() : AttributeBase() {}
  constexpr explicit SortV(value_type value) : AttributeBase(value) {}

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

#endif  // GVIZARD_ATTRS_SORTV_HPP_
