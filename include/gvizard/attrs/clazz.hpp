#ifndef GVIZARD_ATTRS_CLAZZ_HPP_
#define GVIZARD_ATTRS_CLAZZ_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Clazz final : public AttributeBase<Clazz, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "class";

  explicit Clazz() : AttributeBase() {}
  explicit Clazz(const value_type& value) : AttributeBase(value) {}
  explicit Clazz(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }
  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type& value) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CLAZZ_HPP_
