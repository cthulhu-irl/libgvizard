#ifndef GVIZARD_ATTRS_EDGE_RELATED_HPP_
#define GVIZARD_ATTRS_EDGE_RELATED_HPP_

#include <variant>
#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

using DirEdgeConstraintsType = std::variant<std::string, bool>;

struct DirEdgeConstraints final
  : public AttributeBase<DirEdgeConstraints, DirEdgeConstraintsType>
{
  using value_type = DirEdgeConstraintsType;

  constexpr static const char * const name = "diredgeconstraints";

  DirEdgeConstraints() : AttributeBase(get_default_value()) {}
  DirEdgeConstraints(value_type value) : AttributeBase(value) {}

  static value_type get_default_value() noexcept { return false; }

  static bool is_default(value_type value)
  {
    return value == get_default_value();
  }

  static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_EDGE_RELATED_HPP_
