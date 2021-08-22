#ifndef GVIZARD_ATTRS_TAIL_RELATED_HPP_
#define GVIZARD_ATTRS_TAIL_RELATED_HPP_

#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrs {

using TailLPType = std::optional<attrtypes::Point2D<double>>;

struct TailLP final : public AttributeBase<TailLP, TailLPType> {
  using value_type = TailLPType;

  constexpr static const char * const name = "tail_lp";

  constexpr explicit TailLP() : AttributeBase() {}
  constexpr explicit TailLP(const value_type& value)
    : AttributeBase(value)
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::nullopt;
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

#endif  // GVIZARD_ATTRS_TAIL_RELATED_HPP_
