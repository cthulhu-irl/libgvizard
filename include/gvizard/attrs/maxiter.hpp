#ifndef GVIZARD_ATTRS_MAXITER_HPP_
#define GVIZARD_ATTRS_MAXITER_HPP_

#include <optional>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct MaxIter final
  : public AttributeBase<MaxIter, std::optional<int>>
{
  using value_type = std::optional<int>;

  constexpr static const char * const name = "maxiter";

  constexpr explicit MaxIter() noexcept : AttributeBase() {}
  constexpr explicit MaxIter(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_MAXITER_HPP_
