#ifndef GVIZARD_ATTRS_HEAD_RELATED_HPP_
#define GVIZARD_ATTRS_HEAD_RELATED_HPP_

#include <string>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>
#include <gvizard/attrtypes/escstring.hpp>
#include <gvizard/attrtypes/label.hpp>

namespace gvizard::attrs {

struct HeadLP final
  : public AttributeBase<HeadLP, attrtypes::Point2D<double>>
{
  using value_type = attrtypes::Point2D<double>;

  constexpr static const char * const name = "head_lp";

  constexpr explicit HeadLP() : AttributeBase(get_default_value()) {}
  constexpr explicit HeadLP(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return {0., 0.};
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};


struct HeadClip final : public AttributeBase<HeadClip, bool> {
  using value_type = bool;

  constexpr static const char * const name = "headclip";

  constexpr explicit HeadClip() : AttributeBase(get_default_value()) {}
  constexpr explicit HeadClip(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return true; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};


struct HeadHref final
  : public AttributeBase<HeadHref, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "headhref";

  explicit HeadHref() : AttributeBase(get_default_value()) {}
  explicit HeadHref(const value_type& value) : AttributeBase(value) {}
  explicit HeadHref(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value)
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct HeadLabel final
  : public AttributeBase<HeadLabel, attrtypes::Label<std::string>>
{
  using value_type = attrtypes::Label<std::string>;

  constexpr static const char * const name = "headlabel";

  explicit HeadLabel() : AttributeBase(get_default_value()) {}
  explicit HeadLabel(const value_type& value) : AttributeBase(value) {}
  explicit HeadLabel(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value)
  {
    return value.empty();
  }

  static bool constraint(const value_type& value) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_HEAD_RELATED_HPP_
