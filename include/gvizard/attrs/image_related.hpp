#ifndef GVIZARD_ATTRS_IMAGE_RELATED_HPP_
#define GVIZARD_ATTRS_IMAGE_RELATED_HPP_

#include <string>
#include <variant>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/imagepos.hpp"

namespace gviz::attrs {

struct Image final : public AttributeBase<Image, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "image";

  explicit Image() noexcept : AttributeBase() {}
  explicit Image(const value_type& value) : AttributeBase(value) {}
  explicit Image(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct ImagePath final : public AttributeBase<ImagePath, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "imagepath";

  explicit ImagePath() noexcept : AttributeBase() {}
  explicit ImagePath(const value_type& value) : AttributeBase(value) {}
  explicit ImagePath(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct ImagePos final
  : public AttributeBase<ImagePos, attrtypes::ImagePosEnum>
{
  using value_type = attrtypes::ImagePosEnum;

  constexpr static const char * const name = "imagepos";

  constexpr explicit ImagePos() noexcept : AttributeBase() {}
  constexpr explicit ImagePos(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::ImagePosEnum::mc;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};


using ImageScaleType = std::variant<bool, std::string>;

struct ImageScale final : public AttributeBase<ImageScale, ImageScaleType>
{
  using value_type = ImageScaleType;

  constexpr static const char * const name = "imagescale";

  explicit ImageScale() noexcept : AttributeBase() {}
  explicit ImageScale(const value_type& value) : AttributeBase(value) {}
  explicit ImageScale(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return false; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_IMAGE_RELATED_HPP_
