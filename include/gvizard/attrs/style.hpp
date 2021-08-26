#ifndef GVIZARD_ATTRS_STYLE_HPP_
#define GVIZARD_ATTRS_STYLE_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/style.hpp>

namespace gvizard::attrs {

struct Style final : public AttributeBase<Style, attrtypes::Style> {
  using value_type = attrtypes::Style;

  constexpr static const char * const name = "style";

  explicit Style() noexcept : AttributeBase() {}
  explicit Style(const value_type& value) : AttributeBase(value) {}
  explicit Style(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.items.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_STYLE_HPP_
