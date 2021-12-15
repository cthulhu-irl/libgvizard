#ifndef GVIZARD_ATTRS_SEP_HPP_
#define GVIZARD_ATTRS_SEP_HPP_

#include <variant>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/addible.hpp"
#include "gvizard/attrtypes/point.hpp"

namespace gvizard::attrs {

using SepType =
  std::variant<
    attrtypes::AddDouble, attrtypes::Addible<attrtypes::PointType<double>>>;

struct Sep final : public AttributeBase<Sep, SepType> {
  using value_type = SepType;

  constexpr static const char * const name = "sep";

  constexpr explicit Sep() noexcept : AttributeBase() {}
  constexpr explicit Sep(const value_type& value)
    : AttributeBase(value)
  {}
  constexpr explicit Sep(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return +attrtypes::AddDouble::make(4.);
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

#endif  // GVIZARD_ATTRS_SEP_HPP_
