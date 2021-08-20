#ifndef GVIZARD_ATTRS_IMAGE_RELATED_HPP_
#define GVIZARD_ATTRS_IMAGE_RELATED_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Image final : public AttributeBase<Image, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "image";

  explicit Image() : AttributeBase(get_default_value()) {}
  explicit Image(const value_type& value) : AttributeBase(value) {}
  explicit Image(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct ImagePath final : public AttributeBase<ImagePath, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "image";

  explicit ImagePath() : AttributeBase(get_default_value()) {}
  explicit ImagePath(const value_type& value) : AttributeBase(value) {}
  explicit ImagePath(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_IMAGE_RELATED_HPP_
