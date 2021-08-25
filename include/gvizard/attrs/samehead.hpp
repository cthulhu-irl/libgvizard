#ifndef GVIZARD_ATTRS_SAMEHEAD_HPP_
#define GVIZARD_ATTRS_SAMEHEAD_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct SameHead final : public AttributeBase<SameHead, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "samehead";

  explicit SameHead() : AttributeBase() {}
  explicit SameHead(const value_type& value) : AttributeBase(value) {}
  explicit SameHead(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SAMEHEAD_HPP_
