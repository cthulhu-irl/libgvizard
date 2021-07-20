#ifndef GVIZARD_ATTRTYPES_ADDIBLE_HPP_
#define GVIZARD_ATTRTYPES_ADDIBLE_HPP_

#include <utility>

namespace gvizard::attrtypes {

enum class AddibleSign : bool {
  neutral = false,
  addible = true
};

template <typename Derived, typename T>
struct AddibleBase {
  T value{};
  AddibleSign addible = AddibleSign::neutral;

  constexpr static Derived
  make(T value, AddibleSign sign = AddibleSign::neutral)
  {
    return AddibleBase{ std::move(value), sign };
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  /* nothing here */
};

struct AddDouble : public AddibleBase<AddDouble, double> {
  constexpr operator double() const { return value; }

  constexpr AddDouble& operator+(double other)
  {
    value += other;
    return *this;
  };

  constexpr AddDouble& operator-(double other)
  {
    value -= other;
    return *this;
  };

  constexpr AddDouble& operator*(double other)
  {
    value *= other;
    return *this;
  };

  constexpr AddDouble& operator/(double other)
  {
    value /= other;
    return *this;
  };
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
