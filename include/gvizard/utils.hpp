#ifndef GVIZARD_UTILS_HPP_
#define GVIZARD_UTILS_HPP_

#include <type_traits>
#include <string_view>
#include <optional>

#include <magic_enum.hpp>

namespace gvizard {
namespace utils {

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

template<class... Ts>
struct LambdaVisitor final : Ts... { using Ts::operator()...; };

template<class... Ts>
LambdaVisitor(Ts...) -> LambdaVisitor<Ts...>;

}  // namespace utils
}  // namespace gvizard

#endif  // GVIZARD_UTILS_HPP_
