#ifndef GVIZARD_ATTRS_LOGICAL_RELATED_HPP_
#define GVIZARD_ATTRS_LOGICAL_RELATED_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct LHead final : public AttributeBase<LHead, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "lhead";

  explicit LHead() : AttributeBase() {}
  explicit LHead(const value_type& value) : AttributeBase(value) {}
  explicit LHead(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) { return value.empty(); }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LOGICAL_RELATED_HPP_
