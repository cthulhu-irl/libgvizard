#ifndef GVIZARD_ATTRS_LABEL_RELATED_HPP_
#define GVIZARD_ATTRS_LABEL_RELATED_HPP_

#include <string>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/label.hpp>

namespace gvizard::attrs {

struct Label final
  : public AttributeBase<Label, attrtypes::Label<std::string>>
{
  using value_type = attrtypes::Label<std::string>;

  constexpr static const char * const name = "label";

  explicit Label() : AttributeBase(get_default_value()) {}
  explicit Label(const value_type& value) : AttributeBase(value) {}
  explicit Label(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value)
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LabelScheme final : public AttributeBase<LabelScheme, int> {
  using value_type = int;

  constexpr static const char * const name = "label_scheme";

  constexpr explicit LabelScheme() : AttributeBase(get_default_value()) {}
  constexpr explicit LabelScheme(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LABEL_RELATED_HPP_
