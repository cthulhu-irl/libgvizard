#ifndef GVIZARD_ATTRS_PAD_HPP_
#define GVIZARD_ATTRS_PAD_HPP_

#include <variant>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using PadType = std::variant<double, attrtypes::PointType<double>>;

struct Pad final : public AttributeBase<Pad, PadType> {
  using value_type = PadType;

  constexpr static const char * const name = "pad";

  constexpr explicit Pad() noexcept : AttributeBase() {}
  constexpr explicit Pad(const value_type& value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return .0555; }

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

#endif  /// GVIZARD_ATTRS_PAD_HPP_
