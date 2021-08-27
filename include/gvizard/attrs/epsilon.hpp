#ifndef GVIZARD_ATTRS_EPSILON_HPP_
#define GVIZARD_ATTRS_EPSILON_HPP_

#include <optional>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Epsilon final : public AttributeBase<Epsilon, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "epsilon";

  constexpr explicit Epsilon() noexcept : AttributeBase() {}
  constexpr explicit Epsilon(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return !value;
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_EPSILON_HPP_
