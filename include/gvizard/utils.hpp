#ifndef GVIZARD_UTILS_HPP_
#define GVIZARD_UTILS_HPP_

#include <cstddef>
#include <memory>
#include <type_traits>
#include <string_view>
#include <optional>
#include <stdexcept>
#include <variant>

#include <magic_enum.hpp>

namespace gvizard {
namespace utils {

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename U>
struct Converter final {
  static_assert(
    std::is_constructible_v<T, U>,
    "given types to converter aren't trivially convertible by constructor."
  );

  constexpr static T convert(const U& obj) { return T(obj); }
  constexpr static T convert(U&& obj) { return T(std::move(obj)); }
};

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

  constexpr operator T() const { return value_; }

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
};

template <typename T,
          typename U = std::size_t,
          std::enable_if_t<std::is_enum_v<T>, bool> = true>
struct EnumHelper final {
  constexpr static auto to_str(const T& value) -> const std::string_view
  {
    return magic_enum::enum_name(value);
  }

  constexpr static auto from_value(const U& value) -> std::optional<T>
  {
    return magic_enum::enum_cast<T>(value);
  }

  constexpr static auto from_index(std::size_t index) -> std::optional<T>
  {
    if (index >= size())
      return std::nullopt;

    return magic_enum::enum_value<T>(index);
  }

  constexpr static auto from_str(const char *str) -> std::optional<T>
  {
    return magic_enum::enum_cast<T>(str);
  }

  constexpr static auto from_str(const std::string_view str)
    -> std::optional<T>
  {
    return magic_enum::enum_cast<T>(std::move(str));
  }

  static auto from_str(const std::string str) -> std::optional<T>
  {
    return magic_enum::enum_cast<T>(std::move(str));
  }

  constexpr static std::size_t size()
  {
    return magic_enum::enum_count<T>();
  }
};

template <typename ...Ts>
struct LambdaVisitor final : Ts... { using Ts::operator()...; };

template <typename ...Ts>
LambdaVisitor(Ts...) -> LambdaVisitor<Ts...>;

template <typename T, typename ...Fs>
constexpr auto LambdaVisit(const T& arg, Fs... fs)
{
  return std::visit(LambdaVisitor{fs...}, arg);
}

template <typename T>
class OptionalRef {
  T* ptr_{nullptr};

 public:
  using value_type           = std::remove_reference_t<T>;
  using reference_type       = value_type&;
  using const_reference_type = const value_type&;
  using pointer_type         = value_type*;
  using const_pointer_type   = const value_type*;

  OptionalRef()                   : ptr_(nullptr) {}
  OptionalRef(reference_type ref) : ptr_(std::addressof(ref)) {}
  OptionalRef(pointer_type ptr)   : ptr_(ptr) {}

  constexpr bool has_value() const noexcept { return bool(ptr_); }

  constexpr auto&       value() noexcept       { return *ptr_; }
  constexpr const auto& value() const noexcept { return *ptr_; }

  template <typename U>
  constexpr auto& value_or(U& other) noexcept
  {
    if (ptr_) return *ptr_;
    else      return other;
  }

  template <typename U>
  constexpr const auto& value_or(const U& other) const noexcept
  {
    if (ptr_) return *ptr_;
    else      return other;
  }

  template <typename F>
  constexpr auto map(F&& func)
    noexcept(noexcept(func(std::declval<T&>())))
    -> std::optional<std::invoke_result_t<F, T&>>
  {
    if (!has_value()) return std::nullopt;
    return { func(value()) };
  }

  template <typename F>
  constexpr auto map(F&& func) const
    noexcept(noexcept(func(std::declval<T&>())))
    -> std::optional<std::invoke_result_t<F, const T&>>
  {
    if (!has_value()) return std::nullopt;
    return { func(value()) };
  }

  template <typename U, typename F>
  constexpr auto map_into(F&& func)
    noexcept(noexcept(U(func(std::declval<T&>()))))
    -> std::optional<std::invoke_result_t<F, T&>>
  {
    if (!has_value()) return U();
    return U(func(value()));
  }

  template <typename U, typename F>
  constexpr auto map_into(F&& func) const
    noexcept(noexcept(func(std::declval<T&>())))
    -> std::optional<std::invoke_result_t<F, const T&>>
  {
    if (!has_value())
      return std::nullopt;

    return U(func(value()));
  }

  constexpr reference_type       operator*()       noexcept { return *ptr_; }
  constexpr const_reference_type operator*() const noexcept { return *ptr_; }

  constexpr pointer_type       operator->()       noexcept { return ptr_; }
  constexpr const_pointer_type operator->() const noexcept { return ptr_; }

  constexpr bool operator==(const OptionalRef other) const noexcept
  {
    return ptr_ == other.ptr_;
  }

  constexpr bool operator!=(const OptionalRef other) const noexcept
  {
    return ptr_ == other.ptr_;
  }

  constexpr operator bool() const noexcept { return bool(ptr_); }
};

inline constexpr auto nulloptref = nullptr;

}  // namespace utils
}  // namespace gvizard

#endif  // GVIZARD_UTILS_HPP_
