#ifndef GVIZARD_ATTRS_LAYER_RELATED_HPP_
#define GVIZARD_ATTRS_LAYER_RELATED_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/layers.hpp"

namespace gviz::attrs {

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


struct Layers final : public AttributeBase<Layers, attrtypes::LayerList>
{
  using value_type = attrtypes::LayerList;

  constexpr static const char * const name = "layers";

  explicit Layers() noexcept : AttributeBase() {}
  explicit Layers(const value_type& value) : AttributeBase(value) {}
  explicit Layers(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LayerSelect final
  : public AttributeBase<LayerSelect, attrtypes::LayerRange>
{
  using value_type = attrtypes::LayerRange;

  constexpr static const char * const name = "layerselect";

  explicit LayerSelect() noexcept : AttributeBase() {}
  explicit LayerSelect(const value_type& value) : AttributeBase(value) {}
  explicit LayerSelect(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LayerSep final : public AttributeBase<LayerSep, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "layersep";

  explicit LayerSep() : AttributeBase() {}
  explicit LayerSep(const value_type& value) : AttributeBase(value) {}
  explicit LayerSep(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return ":\t "; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_LAYER_RELATED_HPP_
