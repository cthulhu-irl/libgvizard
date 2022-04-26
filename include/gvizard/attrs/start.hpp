#ifndef GVIZARD_ATTRS_START_HPP_
#define GVIZARD_ATTRS_START_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/starttype.hpp"

namespace gviz::attrs {

struct Start final : public AttributeBase<Start, attrtypes::StartType> {
  using value_type = attrtypes::StartType;

  constexpr static const char * const name = "start";

  constexpr Start() noexcept : AttributeBase() {}
  constexpr Start(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::StartType{};
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_START_HPP_
