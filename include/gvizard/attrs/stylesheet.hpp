#ifndef GVIZARD_ATTRS_STYLESHEET_HPP_
#define GVIZARD_ATTRS_STYLESHEET_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct StyleSheet final : public AttributeBase<StyleSheet, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "stylesheet";

  explicit StyleSheet() : AttributeBase() {}
  explicit StyleSheet(const value_type& value) : AttributeBase(value) {}
  explicit StyleSheet(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_STYLESHEET_HPP_
