#ifndef GVIZARD_ATTRS_TAIL_RELATED_HPP_
#define GVIZARD_ATTRS_TAIL_RELATED_HPP_

#include <string>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>
#include <gvizard/attrtypes/label.hpp>

namespace gvizard::attrs {

using TailLPType = std::optional<attrtypes::Point2D<double>>;

struct TailLP final : public AttributeBase<TailLP, TailLPType> {
  using value_type = TailLPType;

  constexpr static const char * const name = "tail_lp";

  constexpr explicit TailLP() : AttributeBase() {}
  constexpr explicit TailLP(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};


struct TailClip final : public AttributeBase<TailClip, bool> {
  using value_type = bool;

  constexpr static const char * const name = "tailclip";

  constexpr explicit TailClip() : AttributeBase() {}
  constexpr explicit TailClip(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return true; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};


struct TailHref final
  : public AttributeBase<TailHref, attrtypes::Label<std::string>>
{
  using value_type = attrtypes::Label<std::string>;

  constexpr static const char * const name = "tailhref";

  explicit TailHref() : AttributeBase() {}
  explicit TailHref(const value_type& value) : AttributeBase(value) {}
  explicit TailHref(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return value_type(""); }

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

#endif  // GVIZARD_ATTRS_TAIL_RELATED_HPP_
