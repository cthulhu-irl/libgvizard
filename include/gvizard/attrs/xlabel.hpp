#ifndef GVIZARD_ATTRS_XLABEL_HPP_
#define GVIZARD_ATTRS_XLABEL_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct XLabel final : public AttributeBase<XLabel, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "xlabel";

  explicit XLabel() noexcept : AttributeBase() {}
  explicit XLabel(const value_type& value) : AttributeBase(value) {}
  explicit XLabel(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_XLABEL_HPP_
