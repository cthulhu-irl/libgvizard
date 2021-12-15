#ifndef GVIZARD_ATTRS_MODE_HPP_
#define GVIZARD_ATTRS_MODE_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Mode final : public AttributeBase<Mode, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "mode";

  explicit Mode() : AttributeBase() {}
  explicit Mode(const value_type& value) : AttributeBase(value) {}
  explicit Mode(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return "major"; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_MODE_HPP_
