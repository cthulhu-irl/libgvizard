#ifndef GVIZARD_ATTRS_PACKMODE_HPP_
#define GVIZARD_ATTRS_PACKMODE_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/packmode.hpp"

namespace gvizard::attrs {

struct PackMode final
  : public AttributeBase<PackMode, attrtypes::PackMode>
{
  using value_type = attrtypes::PackMode;

  constexpr static const char * const name = "packmode";

  constexpr explicit PackMode() noexcept : AttributeBase() {}
  constexpr explicit PackMode(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept { return {}; }

  constexpr static bool is_default(const value_type& value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_PACKMODE_HPP_
