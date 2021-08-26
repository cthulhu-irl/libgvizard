#ifndef GVIZARD_ATTRS_DPI_HPP_
#define GVIZARD_ATTRS_DPI_HPP_

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Dpi final : public AttributeBase<Dpi, double> {
  using value_type = double;

  constexpr static const char * const name = "dpi";

  constexpr explicit Dpi() noexcept : AttributeBase() {}
  constexpr explicit Dpi(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 96.0;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0.0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_DPI_HPP_
