#ifndef GVIZARD_ATTRS_RECTS_HPP_
#define GVIZARD_ATTRS_RECTS_HPP_

#include <optional>

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/rect.hpp>

namespace gvizard::attrs {

using RectsType = std::optional<attrtypes::Rect>;

struct Rects final : public AttributeBase<Rects, RectsType>
{
  using value_type = RectsType;

  constexpr static const char * const name = "rects";

  constexpr explicit Rects() noexcept : AttributeBase() {}
  constexpr explicit Rects(const value_type& value)
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

#endif  // GVIZARD_ATTRS_RECTS_HPP_
