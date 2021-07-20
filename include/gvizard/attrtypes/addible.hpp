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
    return { { std::move(value), sign } };
  }

  friend constexpr Derived operator+(const Derived& obj)
  {
    return make( obj.value, AddibleSign::addible );
  }

  friend constexpr Derived operator+(Derived&& obj)
  {
    return make( std::move(obj.value), AddibleSign::addible );
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  /* nothing here */
};

struct AddDouble : public AddibleBase<AddDouble, double> {
  constexpr operator double() const { return value; }

  friend constexpr AddDouble
  operator+(const AddDouble& lhs, const AddDouble& rhs)
  {
    return make( lhs.value + rhs.value, lhs.addible );
  }

  friend constexpr AddDouble
  operator-(const AddDouble& lhs, const AddDouble& rhs)
  {
    return make( lhs.value - rhs.value, lhs.addible );
  }

  friend constexpr AddDouble
  operator*(const AddDouble& lhs, const AddDouble& rhs)
  {
    return make( lhs.value * rhs.value, lhs.addible );
  }

  friend constexpr AddDouble
  operator/(const AddDouble& lhs, const AddDouble& rhs)
  {
    return make( lhs.value / rhs.value, lhs.addible );
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
