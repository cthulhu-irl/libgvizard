#ifndef GVIZARD_ATTRS_ARROWS_HPP_
#define GVIZARD_ATTRS_ARROWS_HPP_

#include <optional>

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/arrowtype.hpp"

namespace gvizard::attrs {

struct ArrowHead final
  : public AttributeBase<ArrowHead, attrtypes::ArrowType>
{
  using value_type = attrtypes::ArrowType;

  constexpr static const char * const name = "arrowhead";

  constexpr ArrowHead() : AttributeBase(get_default_value()) {}
  constexpr ArrowHead(value_type arrow)
    : AttributeBase(std::move(arrow))
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::ArrowType{ attrtypes::arrowshapes::normal };
  }

  constexpr static bool is_default(const value_type& arrow) noexcept
  {
    return arrow == attrtypes::arrowshapes::none
        || arrow == attrtypes::arrowshapes::normal;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

struct ArrowTail final
  : public AttributeBase<ArrowHead, attrtypes::ArrowType>
{
  using value_type = attrtypes::ArrowType;

  constexpr static const char * const name = "arrowtail";

  constexpr ArrowTail() : AttributeBase(get_default_value()) {}
  constexpr ArrowTail(value_type arrow)
    : AttributeBase(std::move(arrow))
  {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::ArrowType{ attrtypes::arrowshapes::normal };
  }

  constexpr static bool is_default(const value_type& arrow) noexcept
  {
    return arrow == attrtypes::arrowshapes::none
        || arrow == attrtypes::arrowshapes::normal;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

struct ArrowSize final : public AttributeBase<ArrowSize, double> {
  using value_type = double;

  constexpr static const char * const name = "arrowsize";

  constexpr ArrowSize() : AttributeBase(get_default_value()) {}
  constexpr ArrowSize(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return 1.0;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value > 0.0;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_ARROWS_HPP_
