#ifndef GVIZARD_ATTRS_VIEWPORT_HPP_
#define GVIZARD_ATTRS_VIEWPORT_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/viewport.hpp"

namespace gviz::attrs {

struct ViewPort final
  : public AttributeBase<ViewPort, attrtypes::ViewPortType>
{
  using value_type = attrtypes::ViewPortType;

  constexpr static const char * const name = "viewport";

  explicit ViewPort() noexcept : AttributeBase() {}
  explicit ViewPort(const value_type& value) : AttributeBase(value) {}
  explicit ViewPort(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept
  {
    return attrtypes::ViewPortXY{};
  }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_VIEWPORT_HPP_
