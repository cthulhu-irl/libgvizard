#ifndef GVIZARD_ATTRS_URL_HPP_
#define GVIZARD_ATTRS_URL_HPP_

#include <string>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/escstring.hpp"

namespace gvizard::attrs {

struct URL final
  : public AttributeBase<URL, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "URL";

  explicit URL() noexcept : AttributeBase() {}
  explicit URL(const value_type& value) : AttributeBase(value) {}
  explicit URL(value_type&& value) : AttributeBase(std::move(value)) {}

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

#endif  // GVIZARD_ATTRS_URL_HPP_
