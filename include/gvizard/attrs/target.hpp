#ifndef GVIZARD_ATTRS_TARGET_HPP_
#define GVIZARD_ATTRS_TARGET_HPP_

#include <string>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/escstring.hpp>

namespace gvizard::attrs {

struct Target final
  : public AttributeBase<Target, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "target";

  explicit Target() noexcept : AttributeBase() {}
  explicit Target(const value_type& value) : AttributeBase(value) {}
  explicit Target(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return value_type({}); }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_TARGET_HPP_
