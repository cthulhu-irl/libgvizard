#ifndef GVIZARD_ATTRS_FIXEDSIZE_HPP_
#define GVIZARD_ATTRS_FIXEDSIZE_HPP_

#include <string>
#include <variant>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

using FixedSizeType = std::variant<bool, std::string>;

struct FixedSize final : public AttributeBase<FixedSize, FixedSizeType> {
  using value_type = FixedSizeType;

  constexpr static const char * const name = "fixedsize";

  explicit FixedSize() : AttributeBase() {}
  explicit FixedSize(const value_type& value) : AttributeBase(value) {}
  explicit FixedSize(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return false; }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_FIXEDSIZE_HPP_
