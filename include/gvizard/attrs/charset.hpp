#ifndef GVIZARD_ATTRS_CHARSET_HPP_
#define GVIZARD_ATTRS_CHARSET_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gvizard::attrs {

struct Charset final : public AttributeBase<Charset, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "charset";

  explicit Charset() : AttributeBase() {}
  explicit Charset(const value_type& value) : AttributeBase(value) {}
  explicit Charset(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return "UTF-8"; }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type& value) { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_CHARSET_HPP_
