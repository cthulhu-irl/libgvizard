#ifndef GVIZARD_ATTRS_RATIO_HPP_
#define GVIZARD_ATTRS_RATIO_HPP_

#include <string>
#include <variant>
#include <optional>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

using RatioType = std::optional<std::variant<double, std::string>>;

struct Ratio final
  : public AttributeBase<Ratio, RatioType>
{
  using value_type = RatioType;

  constexpr static const char * const name = "ratio";

  explicit Ratio() noexcept : AttributeBase() {}
  explicit Ratio(const value_type& value) : AttributeBase(value) {}
  explicit Ratio(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return std::nullopt; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_RATIO_HPP_
