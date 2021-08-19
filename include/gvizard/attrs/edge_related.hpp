#ifndef GVIZARD_ATTRS_EDGE_RELATED_HPP_
#define GVIZARD_ATTRS_EDGE_RELATED_HPP_

#include <string>
#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/escstring.hpp>

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


struct EdgeHref final
  : public AttributeBase<EdgeHref, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "edgehref";

  EdgeHref() : AttributeBase() {}
  EdgeHref(const value_type& value) : AttributeBase(value) {}
  EdgeHref(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value)
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct EdgeTarget final
  : public AttributeBase<EdgeTarget, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "edgetarget";

  EdgeTarget() : AttributeBase() {}
  EdgeTarget(const value_type& value) : AttributeBase(value) {}
  EdgeTarget(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return value_type(""); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct EdgeTooltip final
  : public AttributeBase<EdgeTooltip, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "edgetooltip";

  EdgeTooltip() : AttributeBase() {}
  EdgeTooltip(const value_type& value) : AttributeBase(value) {}
  EdgeTooltip(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct EdgeURL final
  : public AttributeBase<EdgeURL, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "edgeurl";

  EdgeURL() : AttributeBase() {}
  EdgeURL(const value_type& value) : AttributeBase(value) {}
  EdgeURL(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_EDGE_RELATED_HPP_
