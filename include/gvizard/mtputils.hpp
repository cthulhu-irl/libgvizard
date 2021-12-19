#ifndef GVIZARD_MTPUTILS_HPP_
#define GVIZARD_MTPUTILS_HPP_

#include <cstddef>
#include <type_traits>
#include <utility>

namespace gvizard {
namespace mtp {

namespace impl {
    template <typename T, typename... Ts>
    constexpr inline bool unique_in = (0 + ... + std::is_same_v<T, Ts>) == 1;
}  // namespace impl

template <typename... Ts>
struct all_unique
 : std::bool_constant<(true && ... && impl::unique_in<Ts, Ts...>)> {};

template <typename... Ts>
constexpr inline bool all_unique_v = all_unique<Ts...>::value;


template <typename Base, typename... Ts>
struct all_derive_from
 : std::bool_constant<(true && ... && std::is_base_of_v<Base, Ts>)> {};

template <typename... Ts>
constexpr inline bool all_derive_from_v = all_derive_from<Ts...>::value;

struct identity {
  template <typename T>
  constexpr T&& operator()(T&& arg) const noexcept
  {
    return std::forward<T>(arg);
  }
};

template <typename T>
struct always {
  T value;

  template <typename U>
  constexpr T operator()(U&&) const
  {
    return value;
  }
};

template <typename T, T value>
struct always_ct {
  template <typename U>
  constexpr T operator()(U&&) const noexcept
  {
    return value;
  }
};

template <typename T>
struct staticptr_caster {
  using pointer_type =
    std::add_pointer_t<std::remove_pointer_t<std::remove_reference_t<T>>>;

  template <typename U>
  constexpr pointer_type operator()(U&& arg) const noexcept
  {
    return static_cast<pointer_type>(&arg);
  }
};

template <typename ...Ts>
struct Expandable {
  template <template <typename...> typename Consumer, typename ...Us>
  using expand_for_t = Consumer<Ts..., Us...>;

  template <template <typename...> typename Consumer, typename ...Us>
  using rexpand_for_t = Consumer<Us..., Ts...>;
};

template <typename ...Ts>
struct TypeInfo : public Expandable<Ts...> {
  constexpr static auto size = sizeof...(Ts);
};

template <typename T, typename ...Ts>
struct TypeInfo<T, Ts...> : public Expandable<T, Ts...> {
  using first = T;
  constexpr static auto rest = TypeInfo<Ts...>{};

  constexpr static auto size = sizeof...(Ts);
};


template <typename ...TypeInfos>
struct MixTypeInfo {};

template <>
struct MixTypeInfo<> { using type = TypeInfo<>; };

template <typename TI>
struct MixTypeInfo<TI> { using type = TI; };

template <typename TI, typename ...TypeInfos>
struct MixTypeInfo<TI, TypeInfos...> {

  template <typename ...Ts>
  struct mixer {
    template <typename ...Us>
    struct inner {
      using type = TypeInfo<Ts..., Us...>;
    };
  };

  using mixer_type = typename TI::template expand_for_t<mixer>;

  using type =
    typename MixTypeInfo<TypeInfos...>
      ::type::template expand_for_t<mixer_type::template inner>::type;
};

template <typename ...Ts>
using mix_typeinfo_t = typename MixTypeInfo<Ts...>::type;


template <std::size_t I, typename ...Ts>
struct PackDrop { using type = TypeInfo<Ts...>; };

template <std::size_t I, typename T, typename ...Ts>
struct PackDrop<I, T, Ts...> {
  using type = 
    typename std::conditional<
      I == 0,
        TypeInfo<T, Ts...>,
        typename PackDrop<I-1, Ts...>::type
    >::type;
};

namespace impl {

template <std::size_t I, typename X, typename ...Ts>
struct find_type_index_in_impl {
  static constexpr std::size_t value = 0;
};

template <std::size_t I, typename X, typename T, typename ...Ts>
struct find_type_index_in_impl<I, X, T, Ts...> {
  static constexpr std::size_t value =
      std::is_same_v<X, T>
      ? I
      : find_type_index_in_impl<I, X, Ts...>::value;
};

} // namespace detail

template <typename X, typename ...Ts>
struct find_type_index_in {
  static constexpr std::size_t value =
     impl::find_type_index_in_impl<1, X, Ts...>::value;
};

template <typename X, typename ...Ts>
constexpr inline std::size_t find_type_index_in_v =
                                find_type_index_in<X, Ts...>::value;

template <typename X, typename ...Ts>
struct has_type_in
  : std::bool_constant<(true && ... && std::is_same_v<X, Ts>)>
{};

template <typename X, typename ...Ts>
constexpr inline bool has_type_in_v = has_type_in<X, Ts...>::value;

template <typename T,
          std::size_t StartI, std::size_t EndI, std::size_t StepI = 1>
struct array_atoi_ct {
  constexpr static std::size_t size = (EndI - StartI) / StepI;

  T array[size];

  constexpr array_atoi_ct()
  {
    for (auto i = 0; i < size; ++i)
      array[i] = T(i * StepI);
  }
};

}  // namespace mtp
}  // namespace gvizard

#endif  // GVIZARD_MTPUTILS_HPP_
