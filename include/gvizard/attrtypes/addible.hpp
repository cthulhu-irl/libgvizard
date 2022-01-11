#ifndef GVIZARD_ATTRTYPES_ADDIBLE_HPP_
#define GVIZARD_ATTRTYPES_ADDIBLE_HPP_

#include <utility>

namespace gvizard::attrtypes {

enum class AddibleSign : bool {
  neutral = false,
  addible = true
};

template <typename T>
struct Addible {
  using value_type = T;

  T value{};
  AddibleSign addible = AddibleSign::neutral;

  constexpr Addible(T value, AddibleSign sign = AddibleSign::neutral)
    : value(std::move(value))
    , addible(sign)
  {}

  constexpr T map(T other) const
  {
    return bool(addible) ? (value + std::move(other)) : other;
  }

  constexpr operator value_type() const { return value; }
};

struct AddDouble : public Addible<double> {
  using Addible::Addible;
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
