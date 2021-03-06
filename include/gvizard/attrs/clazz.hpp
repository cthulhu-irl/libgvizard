#ifndef GVIZARD_ATTRS_CLAZZ_HPP_
#define GVIZARD_ATTRS_CLAZZ_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Clazz final : public AttributeBase<Clazz, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "class";

  explicit Clazz() noexcept : AttributeBase() {}
  explicit Clazz(const value_type& value) : AttributeBase(value) {}
  explicit Clazz(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }
  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type& value) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_CLAZZ_HPP_
