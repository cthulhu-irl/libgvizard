#ifndef GVIZARD_ATTRS_RANKSEP_HPP_
#define GVIZARD_ATTRS_RANKSEP_HPP_

#include <vector>
#include <variant>
#include <optional>

#include "gvizard/attribute.hpp"

#include "gvizard/utils.hpp"

namespace gviz::attrs {

using RankSepType =
  std::optional<std::variant<double, std::vector<double>>>;

struct RankSep final : public AttributeBase<RankSep, RankSepType> {
  using value_type = RankSepType;

  constexpr static const char * const name = "ranksep";

  explicit RankSep() noexcept : AttributeBase() {}
  explicit RankSep(const value_type& value) : AttributeBase(value) {}
  explicit RankSep(value_type&& value) : AttributeBase(std::move(value)) {}

  static value_type get_default_value() noexcept { return std::nullopt; }

  static bool is_default(const value_type& value)
  {
    return value == get_default_value();
  }

  static bool constraint(const value_type& value) noexcept
  {
    if (!value) return true;

    return utils::LambdaVisit(
      *value,
      [](double x) { return x >= 0.02; },
      [](const std::vector<double>&) { return true; }
    );
  }
};

}  // namespace gviz::attrs

#endif  // GVIZARD_ATTRS_RANKSEP_HPP_
