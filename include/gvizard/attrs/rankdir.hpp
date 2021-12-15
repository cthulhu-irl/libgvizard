#ifndef GVIZARD_ATTRS_RANKDIR_HPP_
#define GVIZARD_ATTRS_RANKDIR_HPP_

#include "gvizard/attribute.hpp"
#include "gvizard/attrtypes/rank.hpp"

namespace gvizard::attrs {

struct RankDir final : public AttributeBase<RankDir, attrtypes::RankDir>
{
  using value_type = attrtypes::RankDir;

  constexpr static const char * const name = "rankdir";

  constexpr RankDir() noexcept : AttributeBase() {}
  constexpr RankDir(value_type value) : AttributeBase(value) {}

  constexpr static value_type get_default_value() noexcept
  {
    return attrtypes::RankDir::top_bottom;
  }

  constexpr static bool is_default(value_type value) noexcept
  {
    return value == get_default_value();
  }

  constexpr static bool constraint(value_type) noexcept { return true; }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_RANKDIR_HPP_
