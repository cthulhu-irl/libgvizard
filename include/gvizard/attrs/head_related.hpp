#ifndef GVIZARD_ATTRS_HEAD_RELATED_HPP_
#define GVIZARD_ATTRS_HEAD_RELATED_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

struct HeadLP final
  : public AttributeBase<HeadLP, attrtypes::Point2D<double>>
{
  using value_type = attrtypes::Point2D<double>;

  constexpr static const char * const name = "head_lp";

  constexpr explicit HeadLP() : AttributeBase(get_default_value()) {}
  constexpr explicit HeadLP(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return {0., 0.};
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_HEAD_RELATED_HPP_
