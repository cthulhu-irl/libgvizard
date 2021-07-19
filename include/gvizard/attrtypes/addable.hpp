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

  static Derived make(T value) {
    return AddibleBase{ AddibleSign::addible, std::move(value) };
  }

  static Derived make(AddibleSign addible, T value)
  {
    return AddibleBase{ AddibleBase{ addible, std::move(value) } };
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  /* nothing here */
};

struct AddDouble : public AddibleBase<AddDouble, double> {
  operator double() const { return value; }

  AddDouble& operator+(double other)
  {
    value += other;
    return *this;
  };

  AddDouble& operator-(double other)
  {
    value -= other;
    return *this;
  };

  AddDouble& operator*(double other)
  {
    value *= other;
    return *this;
  };

  AddDouble& operator/(double other)
  {
    value /= other;
    return *this;
  };
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
