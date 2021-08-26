#ifndef GVIZARD_ATTRS_MODEL_HPP_
#define GVIZARD_ATTRS_MODEL_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Model final : public AttributeBase<Model, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "model";

  explicit Model() : AttributeBase() {}
  explicit Model(const value_type& value) : AttributeBase(value) {}
  explicit Model(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return "shortpath"; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_MODEL_HPP_
