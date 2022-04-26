#ifndef GVIZARD_CONTRACTS_HPP_
#define GVIZARD_CONTRACTS_HPP_

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <optional>

namespace gviz::contracts {

/** Contract is a (monad-like) single container that ensures
 *  its holding value of type `T` is satisfied
 *  by given `constraints` callable protectes.
 */
template <typename T, auto ...constraints>
class Contract {
  static_assert(
    (std::is_same_v<
        std::invoke_result_t<decltype(constraints), const T&>, bool>
      && ... && true),
    "given constraints as template parameter must be callable"
    "by given value type and return bool."
  );

 protected:
  T value_;

  constexpr static void throw_if_invalid(const T& value)
  {
    if (!check(value))
      throw std::invalid_argument("given value didn't pass all constraints");
  }

 public:
  constexpr Contract() : value_{} { throw_if_invalid(value_); }
  constexpr Contract(const T& v) : value_{v} { throw_if_invalid(value_); }
  constexpr Contract(T&& v) : value_{std::move(v)} { throw_if_invalid(value_); }

  constexpr T value() const { return value_; }

  constexpr bool assign(const T& value)
  {
    if (!check(value)) return false;
    value_ = value;
    return true;
  }

  constexpr bool assign(T&& value)
  {
    if (!check(value)) return false;
    value_ = std::move(value);
    return true;
  }

  constexpr static bool check(const T& value)
  {
    return (constraints(value) && ... && true);
  }

  constexpr static std::optional<T> constrain(const T& value)
  {
    if (!check(value)) return std::nullopt;
    return value;
  }

  constexpr static std::optional<T> constrain(T&& value)
  {
    if (!check(value)) return std::nullopt;
    return std::move(value);
  }

  // comparison operators
  template <typename U>
  constexpr auto operator==(const U& other) const { return value() == other; }
  template <typename U>
  constexpr auto operator!=(const T& other) const { return value() != other; }

  template <typename U>
  constexpr auto operator<(const U& other) const { return value() < other; }
  template <typename U>
  constexpr auto operator>(const U& other) const { return value() > other; }

  template <typename U>
  constexpr auto operator<=(const U& other) const { return value() <= other; }
  template <typename U>
  constexpr auto operator>=(const U& other) const { return value() >= other; }

  constexpr auto operator->() const noexcept { return std::addressof(value_); }
  constexpr auto operator*()  const noexcept { return value();                }

  constexpr operator T() const { return value_; }
};

namespace detail {

template <typename T, T min, T max>
constexpr bool ranged_constraint(const T& val)
{
  return (min <= val) && (val <= max);
};

template <typename T, T base>
constexpr bool lesseqed_constraint(const T& val) { return base >= val; };

template <typename T, T base>
constexpr bool greatereqed_constraint(const T& val) { return base <= val; };

}  // namespace detail

template <typename T, T min, T max>
using Ranged = Contract<T, detail::ranged_constraint<T, min, max>>;

template <typename T, T base>
using LessEqed = Contract<T, detail::lesseqed_constraint<T, base>>;

template <typename T, T base>
using GreaterEqed = Contract<T, detail::greatereqed_constraint<T, base>>;

}  // namespace gviz::contracts

#endif  // GVIZARD_CONTRACTS_HPP_
