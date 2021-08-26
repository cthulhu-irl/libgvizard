#ifndef GVIZARD_ATTRS_DIR_HPP_
#define GVIZARD_ATTRS_DIR_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/dirtype.hpp>

namespace gvizard::attrs {

struct Dir final : public AttributeBase<Dir, attrtypes::DirType> {
  using value_type = attrtypes::DirType;

  constexpr static const char * const name = "dir";

  constexpr Dir() noexcept : AttributeBase() {}
  constexpr Dir(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::DirType::none;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DIR_HPP_
