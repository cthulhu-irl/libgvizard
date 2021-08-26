#ifndef GVIZARD_ATTRS_ESEP_HPP_
#define GVIZARD_ATTRS_ESEP_HPP_

#include <variant>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/addible.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using EsepType =
  std::variant<attrtypes::AddDouble,
               attrtypes::Addible<attrtypes::Point2D<double>>>;

struct Esep final : public AttributeBase<Esep, EsepType> {
  using value_type = EsepType;

  constexpr static const char * const name = "esep";

  constexpr explicit Esep() noexcept : AttributeBase() {}
  constexpr explicit Esep(const value_type& value)
    : AttributeBase(value)
  {}
  constexpr explicit Esep(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return +attrtypes::AddDouble::make(3.0);
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

#endif  // GVIZARD_ATTRS_ESEP_HPP_
