#ifndef GVIZARD_ATTRS_ORDERING_HPP_
#define GVIZARD_ATTRS_ORDERING_HPP_

#include <string>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Ordering final : public AttributeBase<Ordering, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "ordering";

  explicit Ordering() noexcept : AttributeBase() {}
  explicit Ordering(const value_type& value) : AttributeBase(value) {}
  explicit Ordering(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_ORDERING_HPP_
