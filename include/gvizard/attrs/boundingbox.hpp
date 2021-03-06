#ifndef GVIZARD_ATTRS_BOUNDINGBOX_HPP_
#define GVIZARD_ATTRS_BOUNDINGBOX_HPP_

#include <optional>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/rect.hpp"

namespace gviz::attrs {

struct BoundingBox final
  : public AttributeBase<BoundingBox, std::optional<attrtypes::Rect>>
{
  using value_type = std::optional<attrtypes::Rect>;

  constexpr static const char * const name = "bb";

  constexpr explicit BoundingBox() noexcept : AttributeBase() {}
  constexpr explicit BoundingBox(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return !value;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_BOUNDINGBOX_HPP_
