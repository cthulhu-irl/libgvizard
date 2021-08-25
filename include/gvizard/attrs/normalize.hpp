#ifndef GVIZARD_ATTRS_NORMALIZE_HPP_
#define GVIZARD_ATTRS_NORMALIZE_HPP_

#include <variant>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

using NormalizeType = std::variant<bool, double>;

struct Normalize final : public AttributeBase<Normalize, NormalizeType> {
  using value_type = NormalizeType;

  constexpr static const char * const name = "normalize";

  constexpr explicit Normalize() : AttributeBase() {}
  constexpr explicit Normalize(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_NORMALIZE_HPP_
