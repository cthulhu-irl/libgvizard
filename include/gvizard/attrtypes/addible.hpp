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
  using value_type = T;

  T value{};
  AddibleSign addible = AddibleSign::neutral;

  constexpr static Derived
  make(T value, AddibleSign sign = AddibleSign::neutral)
  {
    return Derived(std::move(value), sign);
  }

  constexpr operator value_type() const { return value; }

  constexpr bool operator==(const AddibleBase& other) const
  {
    return addible == other.addible && value == other.value;
  }

  constexpr bool operator!=(const AddibleBase& other) const
  {
    return addible != other.addible || value != other.value;
  }

  constexpr bool operator==(const value_type& other) const
  {
    return addible == AddibleSign::neutral && value == other;
  }

  constexpr bool operator!=(const value_type& other) const
  {
    return addible != AddibleSign::neutral || value != other;
  }

  constexpr Derived operator+() const&
  {
    return make( value, AddibleSign::addible );
  }

  constexpr Derived operator+() &&
  {
    return make( std::move(value), AddibleSign::addible );
  }

  constexpr Derived operator+(const Derived& rhs) const&
  {
    return make( value + rhs.value, addible );
  }

  constexpr Derived operator+(Derived&& rhs) const&
  {
    return make( value + std::move(rhs.value), addible );
  }

  constexpr Derived operator+(const Derived& rhs) &&
  {
    return make( std::move(value) + rhs.value, addible );
  }

  constexpr Derived operator+(Derived&& rhs) &&
  {
    return make( std::move(value) + std::move(rhs.value), addible );
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  constexpr explicit
  Addible(const T& value, AddibleSign sign = AddibleSign::neutral)
    : AddibleBase<Addible<T>, T>{value, sign}
  {}

  constexpr explicit
  Addible(T&& value, AddibleSign sign = AddibleSign::neutral)
    : AddibleBase<Addible<T>, T>{std::move(value), sign}
  {}
};

struct AddDouble : public AddibleBase<AddDouble, double> {
  constexpr explicit
  AddDouble(double value, AddibleSign sign = AddibleSign::neutral)
    : AddibleBase{value, sign}
  {}

  constexpr AddDouble operator+(const AddDouble& rhs)
  {
    return make( value - rhs.value, addible );
  }

  constexpr AddDouble operator-(const AddDouble& rhs)
  {
    return make( value - rhs.value, addible );
  }

  constexpr AddDouble operator*(const AddDouble& rhs)
  {
    return make( value * rhs.value, addible );
  }

  constexpr AddDouble operator/(const AddDouble& rhs)
  {
    return make( value / rhs.value, addible );
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
