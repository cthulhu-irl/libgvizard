#ifndef GVIZARD_ATTRS_OUTPUTORDER_HPP_
#define GVIZARD_ATTRS_OUTPUTORDER_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/outputmode.hpp"

namespace gvizard::attrs {

struct OutputOrder final
  : public AttributeBase<OutputOrder, attrtypes::OutputMode>
{
  using value_type = attrtypes::OutputMode;

  constexpr static const char * const name = "outputorder";

  constexpr OutputOrder() noexcept : AttributeBase() {}
  constexpr OutputOrder(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::OutputMode::breadthfirst;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_OUTPUTORDER_HPP_
