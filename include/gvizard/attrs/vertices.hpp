#ifndef GVIZARD_ATTRS_VERTICES_HPP_
#define GVIZARD_ATTRS_VERTICES_HPP_

#include <vector>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using VerticesType = std::vector<attrtypes::PointType<double>>;

struct Vertices final : public AttributeBase<Vertices, VerticesType>
{
  using value_type = VerticesType;

  constexpr static const char * const name = "vertices";

  explicit Vertices() noexcept : AttributeBase() {}
  explicit Vertices(const value_type& value) : AttributeBase(value) {}
  explicit Vertices(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_VERTICES_HPP_
