#ifndef GVIZARD_ATTRS_PAGEDIR_HPP_
#define GVIZARD_ATTRS_PAGEDIR_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/pagedir.hpp>

namespace gvizard::attrs {

struct PageDir final : public AttributeBase<PageDir, attrtypes::PageDir>
{
  using value_type = attrtypes::PageDir;

  constexpr static const char * const name = "pagedir";

  constexpr explicit PageDir() noexcept : AttributeBase() {}
  constexpr explicit PageDir(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::PageDir::BL;
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

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_PAGEDIR_HPP_
