#ifndef GVIZARD_ATTRS_POS_HPP_
#define GVIZARD_ATTRS_POS_HPP_

#include <vector>
#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>
#include <gvizard/attrtypes/spline.hpp>

namespace gvizard::attrs {

using PosType =
  std::optional<
    std::variant<
      attrtypes::PointType<double>, attrtypes::SplineType<std::vector>>>;

struct Pos final : public AttributeBase<Pos, PosType> {
  using value_type = PosType;

  constexpr static const char * const name = "pos";

  explicit Pos() noexcept : AttributeBase() {}
  explicit Pos(const value_type& value) : AttributeBase(value) {}
  explicit Pos(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return std::nullopt; }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_POS_HPP_
