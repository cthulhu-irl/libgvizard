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
    return Derived{ std::move(value), sign };
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

  friend constexpr Derived operator+(const Derived& obj)
  {
    return make( obj.value, AddibleSign::addible );
  }

  friend constexpr Derived operator+(Derived&& obj)
  {
    return make( std::move(obj.value), AddibleSign::addible );
  }

  friend constexpr Derived
  operator+(const Derived& lhs, const Derived& rhs)
  {
    return make( lhs.value + rhs.value, lhs.addible );
  }

  friend constexpr Derived
  operator+(const Derived& lhs, Derived&& rhs)
  {
    return make( lhs.value + std::move(rhs.value), lhs.addible );
  }

  friend constexpr Derived
  operator+(Derived&& lhs, const Derived& rhs)
  {
    return make( std::move(lhs.value) + rhs.value, lhs.addible );
  }

  friend constexpr Derived
  operator+(Derived&& lhs, Derived&& rhs)
  {
    return make( std::move(lhs.value) + std::move(rhs.value), lhs.addible );
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  /* nothing here */
};

struct AddDouble : public AddibleBase<AddDouble, double> {
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
