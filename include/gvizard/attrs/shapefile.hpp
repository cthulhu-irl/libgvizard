#ifndef GVIZARD_ATTRS_SHAPEFILE_HPP_
#define GVIZARD_ATTRS_SHAPEFILE_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct ShapeFile final : public AttributeBase<ShapeFile, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "shapefile";

  explicit ShapeFile() noexcept : AttributeBase() {}
  explicit ShapeFile(const value_type& value) : AttributeBase(value) {}
  explicit ShapeFile(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_SHAPEFILE_HPP_
