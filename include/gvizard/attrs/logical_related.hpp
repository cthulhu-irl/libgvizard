#ifndef GVIZARD_ATTRS_LOGICAL_RELATED_HPP_
#define GVIZARD_ATTRS_LOGICAL_RELATED_HPP_

#include <string>
#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

struct LHead final : public AttributeBase<LHead, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "lhead";

  explicit LHead() : AttributeBase() {}
  explicit LHead(const value_type& value) : AttributeBase(value) {}
  explicit LHead(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) { return value.empty(); }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LTail final : public AttributeBase<LTail, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "ltail";

  explicit LTail() : AttributeBase() {}
  explicit LTail(const value_type& value) : AttributeBase(value) {}
  explicit LTail(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() { return ""; }

  static bool is_default(const value_type& value) { return value.empty(); }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct LHeight final
  : public AttributeBase<LHeight, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "lheight";

  constexpr explicit LHeight() : AttributeBase() {}
  constexpr explicit LHeight(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};


struct LWidth final
  : public AttributeBase<LWidth, std::optional<double>>
{
  using value_type = std::optional<double>;

  constexpr static const char * const name = "lwidth";

  constexpr explicit LWidth() : AttributeBase() {}
  constexpr explicit LWidth(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};


using LPositionType = std::optional<attrtypes::Point2D<double>>;

struct LPosition final : public AttributeBase<LPosition, LPositionType>
{
  using value_type = LPositionType;

  constexpr static const char * const name = "lposition";

  constexpr explicit LPosition() : AttributeBase() {}
  constexpr explicit LPosition(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_LOGICAL_RELATED_HPP_
