#ifndef GVIZARD_ATTRS_HREF_HPP_
#define GVIZARD_ATTRS_HREF_HPP_

#include <string>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/escstring.hpp"

namespace gviz::attrs {

struct Href final
  : public AttributeBase<Href, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "href";

  explicit Href() noexcept : AttributeBase() {}
  explicit Href(const value_type& value) : AttributeBase(value) {}
  explicit Href(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_HREF_HPP_
