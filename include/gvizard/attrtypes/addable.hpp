#ifndef GVIZARD_ATTRTYPES_ADDIBLE_HPP_
#define GVIZARD_ATTRTYPES_ADDIBLE_HPP_

#include <utility>

namespace gvizard::attrtypes {

enum class AddibleSign {
  neutral = false,
  addible = true
};

template <typename Base, typename T>
struct AddibleBase {
  AddibleSign addible = AddibleSign::neutral;
  T value;

  AddibleBase(T val)
    : addible(AddibleSign::neutral)
    , value(val)
  {}

  AddibleBase(AddibleSign addsign, T val)
    : addible(addsign)
    , value(val)
  {}

  static Base make(T value) {
    return { AddibleSign::addible, std::move(value) };
  }

  static Base make(AddibleSign addible, T value)
  {
    return { AddibleBase{ addible, std::move(value) } };
  }
};

// for arbitrary types from user
template <typename T>
struct Addible : public AddibleBase<Addible<T>, T> {
  /* nothing here */
};

struct AddDouble : public AddibleBase<AddDouble, double> {
  AddDouble& operator+(const AddDouble& other)
  {
    value += other.value;
    return *this;
  };

  AddDouble& operator+(double other)
  {
    value += other;
    return *this;
  };
};


}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ADDIBLE_HPP_
