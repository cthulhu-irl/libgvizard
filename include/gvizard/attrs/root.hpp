#ifndef GVIZARD_ATTRS_ROOT_HPP_
#define GVIZARD_ATTRS_ROOT_HPP_

#include <string>
#include <variant>
#include <optional>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

using RootType = std::optional<std::variant<double, std::string>>;

struct Root final : public AttributeBase<Root, RootType>
{
  using value_type = RootType;

  constexpr static const char * const name = "root";

  explicit Root() noexcept : AttributeBase() {}
  explicit Root(const value_type& value) : AttributeBase(value) {}
  explicit Root(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return std::nullopt; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_ROOT_HPP_
