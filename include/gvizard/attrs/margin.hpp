#ifndef GVIZARD_ATTRS_MARGIN_HPP_
#define GVIZARD_ATTRS_MARGIN_HPP_

#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using MarginType =
  std::optional<std::variant<double, attrtypes::PointType<double>>>;

struct Margin final : public AttributeBase<Margin, MarginType> {
  using value_type = MarginType;

  constexpr static const char * const name = "margin";

  constexpr explicit Margin() noexcept : AttributeBase() {}
  constexpr explicit Margin(const value_type& value)
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

}  // namespace gvizard::attrs

#endif  /// GVIZARD_ATTRS_MARGIN_HPP_
