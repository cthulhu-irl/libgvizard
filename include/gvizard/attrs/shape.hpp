#ifndef GVIZARD_ATTRS_SHAPE_HPP_
#define GVIZARD_ATTRS_SHAPE_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/shape.hpp"

namespace gvizard::attrs {

struct Shape final : public AttributeBase<Shape, attrtypes::ShapeType> {
  using value_type = attrtypes::ShapeType;

  constexpr static const char * const name = "shape";

  constexpr Shape() noexcept : AttributeBase() {}
  constexpr Shape(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::ShapeType::ellipse;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SHAPE_HPP_
