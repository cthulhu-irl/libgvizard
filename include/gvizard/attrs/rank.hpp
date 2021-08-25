#ifndef GVIZARD_ATTRS_RANK_HPP_
#define GVIZARD_ATTRS_RANK_HPP_

#include <gvizard/attribute.hpp>
#include <gvizard/attrtypes/rank.hpp>

namespace gvizard::attrs {

struct Rank final : public AttributeBase<Rank, attrtypes::RankType> {
  using value_type = attrtypes::RankType;

  constexpr static const char * const name = "rank";

  constexpr Rank() : AttributeBase() {}
  constexpr Rank(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::RankType::none;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_RANK_HPP_
