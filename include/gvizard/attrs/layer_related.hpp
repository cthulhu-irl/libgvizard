#ifndef GVIZARD_ATTRS_LAYER_RELATED_HPP_
#define GVIZARD_ATTRS_LAYER_RELATED_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/layers.hpp>

namespace gvizard::attrs {

struct Layer final : public AttributeBase<Layer, attrtypes::LayerRange> {
  using value_type = attrtypes::LayerRange;

  constexpr static const char * const name = "layer";

  explicit Layer() noexcept : AttributeBase() {}
  explicit Layer(const value_type& value) : AttributeBase(value) {}
  explicit Layer(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LayerListSep final
  : public AttributeBase<LayerListSep, std::string>
{
  using value_type = std::string;

  constexpr static const char * const name = "layerlistsep";

  explicit LayerListSep() : AttributeBase() {}
  explicit LayerListSep(const value_type& value) : AttributeBase(value) {}
  explicit LayerListSep(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return ","; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LAYER_RELATED_HPP_
