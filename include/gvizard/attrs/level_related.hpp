#ifndef GVIZARD_ATTRS_LEVEL_RELATED_HPP_
#define GVIZARD_ATTRS_LEVEL_RELATED_HPP_

#include <limits>

#include "gvizard/attribute.hpp"

namespace gviz::attrs {

struct Levels final : public AttributeBase<Levels, unsigned int> {
  using value_type = unsigned int;

  constexpr static const char * const name = "levels";

  constexpr explicit Levels() noexcept : AttributeBase() {}
  constexpr explicit Levels(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return std::numeric_limits<value_type>::max();
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type value) noexcept
  {
    return value >= 0;
  }
};


struct LevelsGap final : public AttributeBase<LevelsGap, double> {
  using value_type = double;

  constexpr static const char * const name = "levelsgap";

  constexpr explicit LevelsGap() noexcept : AttributeBase() {}
  constexpr explicit LevelsGap(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept { return 0.; }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_LEVEL_RELATED_HPP_
