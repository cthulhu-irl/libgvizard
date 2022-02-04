#ifndef GVIZARD_ATTRS_ORIENTATION_HPP_
#define GVIZARD_ATTRS_ORIENTATION_HPP_

#include <string>
#include <variant>

#include "gvizard/attribute.hpp"

#include "gvizard/utils.hpp"

namespace gviz::attrs {

using OrientationType = std::variant<double, std::string>;

struct Orientation final
  : public AttributeBase<Orientation, OrientationType>
{
  using value_type = OrientationType;

  constexpr static const char * const name = "orientation";

  explicit Orientation() noexcept : AttributeBase() {}
  explicit Orientation(const value_type& value) : AttributeBase(value) {}
  explicit Orientation(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return 0.; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type& value) noexcept
  {
    return utils::LambdaVisit(
      value,
      [](double degree) noexcept { return 0. <= degree <= 360.; },
      [](const std::string&) noexcept { return true; }
    );
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_ORIENTATION_HPP_
