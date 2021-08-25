#ifndef GVIZARD_ATTRS_SAMPLEPOINTS_HPP_
#define GVIZARD_ATTRS_SAMPLEPOINTS_HPP_

#include <optional>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct SamplePoints final
  : public AttributeBase<SamplePoints, std::optional<int>>
{
  using value_type = std::optional<int>;

  constexpr static const char * const name = "samplepoints";

  constexpr explicit SamplePoints() : AttributeBase() {}
  constexpr explicit SamplePoints(value_type value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
  }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return !value;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SAMPLEPOINTS_HPP_
