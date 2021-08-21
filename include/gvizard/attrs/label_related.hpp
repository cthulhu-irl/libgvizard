#ifndef GVIZARD_ATTRS_LABEL_RELATED_HPP_
#define GVIZARD_ATTRS_LABEL_RELATED_HPP_

#include <string>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/label.hpp>
#include <gvizard/attrtypes/color.hpp>

#include <gvizard/colors/x11.hpp>

namespace gvizard::attrs {

struct Label final
  : public AttributeBase<Label, attrtypes::Label<std::string>>
{
  using value_type = attrtypes::Label<std::string>;

  constexpr static const char * const name = "label";

  explicit Label() : AttributeBase() {}
  explicit Label(const value_type& value) : AttributeBase(value) {}
  explicit Label(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return value_type(""); }

  static bool is_default(const value_type& value)
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LabelScheme final : public AttributeBase<LabelScheme, int> {
  using value_type = int;

  constexpr static const char * const name = "label_scheme";

  constexpr explicit LabelScheme() : AttributeBase() {}
  constexpr explicit LabelScheme(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};


struct LabelAngle final : public AttributeBase<LabelAngle, double> {
  using value_type = double;

  constexpr static const char * const name = "labelangle";

  constexpr explicit LabelAngle() : AttributeBase() {}
  constexpr explicit LabelAngle(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return -25.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= -180.;
  }
};


struct LabelDistance final : public AttributeBase<LabelDistance, double>
{
  using value_type = double;

  constexpr static const char * const name = "labeldistance";

  constexpr explicit LabelDistance() : AttributeBase() {}
  constexpr explicit LabelDistance(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return 1.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.;
  }
};


struct LabelFloat final : public AttributeBase<LabelFloat, double> {
  using value_type = double;

  constexpr static const char * const name = "labelfloat";

  constexpr explicit LabelFloat() : AttributeBase() {}
  constexpr explicit LabelFloat(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return false; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return true;
  }
};


struct LabelFontColor final
  : public AttributeBase<LabelFontColor, attrtypes::ColorType>
{
  using value_type = attrtypes::ColorType;

  constexpr static const char * const name = "labelfontcolor";

  constexpr explicit LabelFontColor() : AttributeBase() {}
  constexpr explicit LabelFontColor(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return { colors::X11ColorEnum::black };
  }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};


struct LabelFontName final
  : public AttributeBase<LabelFontName, std::string>
{
  using value_type = std::string;

  constexpr static const char * const name = "labelfontname";

  explicit LabelFontName() : AttributeBase() {}
  explicit LabelFontName(const value_type& value) : AttributeBase(value) {}
  explicit LabelFontName(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() { return "Times-Roman"; }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return false; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LABEL_RELATED_HPP_
