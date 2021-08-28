#ifndef GVIZARD_CONTRACTS_HPP_
#define GVIZARD_CONTRACTS_HPP_

#include <gvizard/utils.hpp>

namespace gvizard::contracts {

template <typename T, T min, T max>
constexpr auto ranged_constraint =
  +[](const T& val) { return (min <= val) && (val <= max); };

template <typename T, T min, T max>
using Ranged = utils::Contract<T, ranged_constraint<T, min, max>>;


template <typename T, T base>
constexpr auto lesseqed_constraint =
  +[](const T& val) { return base >= val; };

template <typename T, T base>
using LessEqed = utils::Contract<T, lesseqed_constraint<T, base>>;


template <typename T, T base>
constexpr auto greatereqed_constraint =
  +[](const T& val) { return base <= val; };

template <typename T, T base>
using GreaterEqed = utils::Contract<T, greatereqed_constraint<T, base>>;

}  // namespace gvizard::contracts

#endif  // GVIZARD_CONTRACTS_HPP_
