#ifndef GVIZARD_ATTRS_SAMETAIL_HPP_
#define GVIZARD_ATTRS_SAMETAIL_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct SameTail final : public AttributeBase<SameTail, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "sametail";

  explicit SameTail() noexcept : AttributeBase() {}
  explicit SameTail(const value_type& value) : AttributeBase(value) {}
  explicit SameTail(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SAMETAIL_HPP_
