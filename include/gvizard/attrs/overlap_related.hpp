#ifndef GVIZARD_ATTRS_OVERLAP_RELATED_HPP_
#define GVIZARD_ATTRS_OVERLAP_RELATED_HPP_

#include <string>
#include <variant>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

using OverlapType = std::variant<bool, std::string>;

struct Overlap final : public AttributeBase<Overlap, OverlapType> {
  using value_type = OverlapType;

  constexpr static const char * const name = "overlap";

  explicit Overlap() noexcept : AttributeBase() {}
  explicit Overlap(const value_type& value) : AttributeBase(value) {}
  explicit Overlap(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return true; }

  static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type&) noexcept { return true; }
};


struct OverlapScaling final : public AttributeBase<OverlapScaling, double>
{
  using value_type = double;

  constexpr static const char * const name = "overlap_scaling";

  constexpr explicit OverlapScaling() noexcept : AttributeBase() {}
  constexpr explicit OverlapScaling(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return -4.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= -10000000000;
  }
};


struct OverlapShrink final : public AttributeBase<OverlapShrink, double> {
  using value_type = double;

  constexpr static const char * const name = "overlap_shrink";

  constexpr explicit OverlapShrink() noexcept : AttributeBase() {}
  constexpr explicit OverlapShrink(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return true; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_OVERLAP_RELATED_HPP_
