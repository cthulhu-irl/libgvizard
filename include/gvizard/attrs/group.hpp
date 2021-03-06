#ifndef GVIZARD_ATTRS_GROUP_HPP_
#define GVIZARD_ATTRS_GROUP_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Group final : public AttributeBase<Group, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "group";

  explicit Group() noexcept : AttributeBase() {}
  explicit Group(const value_type& value) : AttributeBase(value) {}
  explicit Group(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_GROUP_HPP_
