#ifndef GVIZARD_ATTRS_QUADTREE_HPP_
#define GVIZARD_ATTRS_QUADTREE_HPP_

#include <variant>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/quadtype.hpp>

namespace gvizard::attrs {

using QuadTreeType = std::variant<attrtypes::QuadType, bool>;

struct QuadTree final : public AttributeBase<QuadTree, QuadTreeType> {
  using value_type = QuadTreeType;

  constexpr static const char * const name = "quadtree";

  constexpr explicit QuadTree() noexcept : AttributeBase() {}
  constexpr explicit QuadTree(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::QuadType::normal;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_QUADTREE_HPP_
