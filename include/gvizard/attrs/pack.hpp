#ifndef GVIZARD_ATTRS_PACK_HPP_
#define GVIZARD_ATTRS_PACK_HPP_

#include <variant>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

using PackType = std::variant<bool, int>;

struct Pack final : public AttributeBase<Pack, PackType> {
  using value_type = PackType;

  constexpr static const char * const name = "pack";

  constexpr explicit Pack() noexcept : AttributeBase() {}
  constexpr explicit Pack(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_PACK_HPP_
