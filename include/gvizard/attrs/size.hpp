#ifndef GVIZARD_ATTRS_SIZE_HPP_
#define GVIZARD_ATTRS_SIZE_HPP_

#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using SizeType =
  std::optional<std::variant<double, attrtypes::Point2D<double>>>;

struct Size final : public AttributeBase<Size, SizeType> {
  using value_type = SizeType;

  constexpr static const char * const name = "size";

  constexpr explicit Size() : AttributeBase() {}
  constexpr explicit Size(const value_type& value)
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

#endif  /// GVIZARD_ATTRS_SIZE_HPP_
