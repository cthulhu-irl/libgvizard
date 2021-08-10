#ifndef GVIZARD_ATTRS_ARROWS_HPP_
#define GVIZARD_ATTRS_ARROWS_HPP_

#include <optional>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/arrowtype.hpp"

namespace gvizard::attrs {

struct ArrowHead final
  : AttributeBase<ArrowHead, std::optional<attrtypes::ArrowType>>
{
  using value_type = std::optional<attrtypes::ArrowType>;

  constexpr static const char * const name = "arrowhead";

  ArrowHead() : AttributeBase(get_default_value()) {}
  ArrowHead(value_type value) : AttributeBase(std::move(value)) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(const value_type& value)
  {
    return !bool(value);
  }

  constexpr static bool constraint(const value_type& value) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_ARROWS_HPP_
