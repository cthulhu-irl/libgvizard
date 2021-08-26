#ifndef GVIZARD_ATTRS_SPLINES_HPP_
#define GVIZARD_ATTRS_SPLINES_HPP_

#include <string>
#include <variant>
#include <optional>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

using SplinesType = std::optional<std::variant<bool, std::string>>;

struct Splines final : public AttributeBase<Splines, SplinesType> {
  using value_type = SplinesType;

  constexpr static const char * const name = "splines";

  explicit Splines() noexcept : AttributeBase() {}
  explicit Splines(const value_type& value) : AttributeBase(value) {}
  explicit Splines(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return std::nullopt; }

  static bool is_default(const value_type& value) noexcept
  {
    return !value;
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SPLINES_HPP_
