#ifndef GVIZARD_ATTRS_SCALE_HPP_
#define GVIZARD_ATTRS_SCALE_HPP_

#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using ScaleType =
  std::optional<std::variant<double, attrtypes::Point2D<double>>>;

struct Scale final : public AttributeBase<Scale, ScaleType> {
  using value_type = ScaleType;

  constexpr static const char * const name = "scale";

  constexpr explicit Scale() : AttributeBase() {}
  constexpr explicit Scale(const value_type& value)
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

#endif  /// GVIZARD_ATTRS_SCALE_HPP_
