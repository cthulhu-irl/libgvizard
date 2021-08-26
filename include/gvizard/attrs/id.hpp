#ifndef GVIZARD_ATTRS_HREF_HPP_
#define GVIZARD_ATTRS_HREF_HPP_

#include <string>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/escstring.hpp>

namespace gvizard::attrs {

struct Id final
  : public AttributeBase<Id, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "id";

  explicit Id() noexcept : AttributeBase() {}
  explicit Id(const value_type& value) : AttributeBase(value) {}
  explicit Id(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_HREF_HPP_
