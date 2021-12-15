#ifndef GVIZARD_ATTRS_LAYOUT_HPP_
#define GVIZARD_ATTRS_LAYOUT_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Layout final : public AttributeBase<Layout, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "layout";

  explicit Layout() noexcept : AttributeBase() {}
  explicit Layout(const value_type& value) : AttributeBase(value) {}
  explicit Layout(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LAYOUT_HPP_
