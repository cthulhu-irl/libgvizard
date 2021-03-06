#ifndef GVIZARD_ATTRS_FONT_RELATED_HPP_
#define GVIZARD_ATTRS_FONT_RELATED_HPP_

#include <string>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/color.hpp"
#include "gvizard/colors/x11.hpp"

namespace gviz::attrs {

struct FontColor final
  : public AttributeBase<FontColor, attrtypes::ColorType>
{
  using value_type = attrtypes::ColorType;

  constexpr static const char * const name = "fontcolor";

  constexpr explicit FontColor() noexcept : AttributeBase() {}
  constexpr explicit FontColor(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return {colors::X11ColorEnum::black};
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};


struct FontName final : public AttributeBase<FontName, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "fontname";

  explicit FontName() : AttributeBase() {}
  explicit FontName(const value_type& value) : AttributeBase(value) {}
  explicit FontName(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return "Times-Roman"; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return false; }
};


struct FontNames final : public AttributeBase<FontNames, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "fontnames";

  explicit FontNames() noexcept : AttributeBase() {}
  explicit FontNames(const value_type& value) : AttributeBase(value) {}
  explicit FontNames(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct FontPath final : public AttributeBase<FontPath, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "fontpath";

  explicit FontPath() noexcept : AttributeBase() {}
  explicit FontPath(const value_type& value) : AttributeBase(value) {}
  explicit FontPath(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct FontSize final : public AttributeBase<FontSize, double> {
  using value_type = double;

  constexpr static const char * const name = "fontsize";

  constexpr explicit FontSize() noexcept : AttributeBase() {}
  constexpr explicit FontSize(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 14.0; };

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 1.0;
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_FONT_RELATED_HPP_
