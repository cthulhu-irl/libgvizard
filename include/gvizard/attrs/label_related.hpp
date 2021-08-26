#ifndef GVIZARD_ATTRS_LABEL_RELATED_HPP_
#define GVIZARD_ATTRS_LABEL_RELATED_HPP_

#include <string>
#include <string_view>

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

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LabelScheme final : public AttributeBase<LabelScheme, int> {
  using value_type = int;

  constexpr static const char * const name = "label_scheme";

  constexpr explicit LabelScheme() noexcept : AttributeBase() {}
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

  constexpr explicit LabelAngle() noexcept : AttributeBase() {}
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

  constexpr explicit LabelDistance() noexcept : AttributeBase() {}
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

  constexpr explicit LabelFloat() noexcept : AttributeBase() {}
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

  constexpr explicit LabelFontColor() noexcept : AttributeBase() {}
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


struct LabelFontSize final : public AttributeBase<LabelFontSize, double>
{
  using value_type = double;

  constexpr static const char * const name = "labelfontsize";

  constexpr explicit LabelFontSize() noexcept : AttributeBase() {}
  constexpr explicit LabelFontSize(value_type value)
    : AttributeBase(value)  
  {}  
  
  constexpr static value_type get_default_value() noexcept { return 14.; }
  
  constexpr static bool is_default(value_type value) noexcept
  {  
    return value == get_default_value();
  }  

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 1.;
  }
};


enum class LabelJustEnum { center = 0, left, right };

struct LabelJust final : public AttributeBase<LabelJust, LabelJustEnum> {
  using value_type = LabelJustEnum;

  constexpr static const char * const name = "labeljust";

  constexpr LabelJust() noexcept : AttributeBase() {}
  constexpr LabelJust(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return LabelJustEnum::center;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }

  operator char() noexcept
  {
    switch (get_value()) {
      case LabelJustEnum::center: return 'c';
      case LabelJustEnum::left:   return 'l';
      case LabelJustEnum::right:  return 'r';
      default:
        return 'c';
    }
  }

  operator std::string_view()
  {
    switch (get_value()) {
      case LabelJustEnum::center: return "c";
      case LabelJustEnum::left:   return "l";
      case LabelJustEnum::right:  return "r";
      default:
        return "c";
    }
  }

  operator std::string() { return std::string(std::string_view(*this)); }
};


enum class LabelLocEnum { _default = 0, top, bottom, center };

struct LabelLoc final : public AttributeBase<LabelLoc, LabelLocEnum> {
  using value_type = LabelLocEnum;

  constexpr static const char * const name = "labelloc";

  constexpr LabelLoc() noexcept : AttributeBase() {}
  constexpr LabelLoc(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return LabelLocEnum::_default;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }

  operator char() noexcept
  {
    switch (get_value()) {
      case LabelLocEnum::center: return 'c';
      case LabelLocEnum::top:    return 't';
      case LabelLocEnum::bottom: return 'b';
      default:
        return ' ';
    }
  }

  operator std::string_view()
  {
    switch (get_value()) {
      case LabelLocEnum::center: return "c";
      case LabelLocEnum::top:    return "t";
      case LabelLocEnum::bottom: return "b";
      default:
        return "";
    }
  }

  operator std::string() { return std::string(std::string_view(*this)); }
};


struct LabelTarget final
  : public AttributeBase<LabelTarget, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "labeltarget";

  explicit LabelTarget() noexcept : AttributeBase() {}
  explicit LabelTarget(const value_type& value) : AttributeBase(value) {}
  explicit LabelTarget(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LabelTooltip final
  : public AttributeBase<LabelTooltip, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "labeltooltip";

  explicit LabelTooltip() noexcept : AttributeBase() {}
  explicit LabelTooltip(const value_type& value) : AttributeBase(value) {}
  explicit LabelTooltip(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LabelURL final
  : public AttributeBase<LabelURL, attrtypes::EscString<std::string>>
{
  using value_type = attrtypes::EscString<std::string>;

  constexpr static const char * const name = "labelURL";

  explicit LabelURL() noexcept : AttributeBase() {}
  explicit LabelURL(const value_type& value) : AttributeBase(value) {}
  explicit LabelURL(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return value_type({}); }

  static bool is_default(const value_type& value) noexcept
  {
    return value.get_format_ref().empty();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LABEL_RELATED_HPP_
