#ifndef GVIZARD_ATTRS_SMOOTHING_HPP_
#define GVIZARD_ATTRS_SMOOTHING_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/smoothtype.hpp>

namespace gvizard::attrs {

struct Smoothing final
  : public AttributeBase<Smoothing, attrtypes::SmoothType>
{
  using value_type = attrtypes::SmoothType;

  constexpr static const char * const name = "smoothing";

  constexpr Smoothing() noexcept : AttributeBase() {}
  constexpr Smoothing(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::SmoothType::none;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_SMOOTHING_HPP_
