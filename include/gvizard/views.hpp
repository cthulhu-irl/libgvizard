#ifndef GVIZARD_VIEWS_HPP_
#define GVIZARD_VIEWS_HPP_

#include <iterator>
#include <optional>
#include <type_traits>
#include <utility>

namespace gviz {

template <typename T, typename F,
          std::enable_if_t<std::is_invocable_v<F, T>, bool> = true>
class CallbackViewIterator {
 public:
  using AdvanceCallback = F;

 private:
  AdvanceCallback  advance_;
  std::optional<T> current_;
  bool             is_sentinel_;

 public:
  constexpr explicit CallbackViewIterator(AdvanceCallback callback)
    : advance_(std::move(callback))
    , current_(std::nullopt)
    , is_sentinel_(true)
  {}

  constexpr explicit CallbackViewIterator(
        AdvanceCallback callback, std::optional<T> init)
    : advance_(std::move(callback))
    , current_(std::move(init))
    , is_sentinel_(init.has_value())
  {}

  constexpr auto has_value() noexcept -> bool
  {
    return current_.has_value();
  }

  constexpr auto next() -> CallbackViewIterator
  {
    if (current_.has_value())
      current_ = advance_(std::move(current_).value());

    return *this;
  }

  constexpr auto next() const -> CallbackViewIterator
  {
    if (current_.has_value())
      return CallbackViewIterator{
        advance_,
        advance_(std::move(current_).value()),
      };

    return *this;
  }

  constexpr auto operator++() -> CallbackViewIterator { return next(); }

  constexpr auto operator++(int) -> CallbackViewIterator {
    auto temp = *this;
    next();
    return temp;
  }

  constexpr auto operator->() { return current_; }
  constexpr auto operator*() const { return current_.value(); }

  constexpr auto operator==(const CallbackViewIterator& other)
  {
    return current_ == other.current_ && is_sentinel_ == other.is_sentinel_;
  }

  constexpr auto operator!=(const CallbackViewIterator& other)
  {
    return current_ != other.current_ || is_sentinel_ != other.is_sentinel_;
  }

  constexpr operator bool() noexcept { return current_.has_value(); }
};

template <typename T, typename F,
          std::enable_if_t<std::is_invocable_v<F, T>, bool> = true>
class CallbackView {
  using AdvanceCallback = F;

  AdvanceCallback  advance;
  std::optional<T> init;

 public:
  CallbackView(AdvanceCallback callback)
    : advance(std::move(callback))
    , init(advance(T()))
  {}

  CallbackView(AdvanceCallback callback, T init)
    : advance(std::move(callback))
    , init(std::move(init))
  {}

  auto begin() & -> CallbackViewIterator<T, F>
  {
    return CallbackViewIterator<T, F>{ advance, init };
  }

  auto begin() && -> CallbackViewIterator<T, F>
  {
    return CallbackViewIterator<T, F>{ std::move(advance), std::move(init) };
  }

  auto begin() const& -> CallbackViewIterator<T, F>
  {
    return CallbackViewIterator<T, F>{ advance, init };
  }

  auto begin() const&& -> CallbackViewIterator<T, F>
  {
    return CallbackViewIterator<T, F>{ std::move(advance), std::move(init) };
  }

  auto end() -> CallbackViewIterator<T, F>
  {
    return CallbackViewIterator<T, F>{ advance };
  }
};

template <typename T,
          typename Iter = decltype(std::begin(std::declval<T&>())),
          typename Sentinel = decltype(std::end(std::declval<T&>())),
          bool Const = false>
class IteratorView {
 public:
  using iter_t     = std::conditional_t<Const, const Iter, Iter>;
  using sentinel_t = std::conditional_t<Const, const Sentinel, Sentinel>;

 private:
  iter_t     iter_begin_;
  sentinel_t iter_end_;

 public:
  constexpr IteratorView(iter_t iter_begin, sentinel_t iter_end)
    : iter_begin_(std::move(iter_begin))
    , iter_end_(std::move(iter_end))
  {}

  constexpr auto begin() -> iter_t { return iter_begin_; }
  constexpr auto end() -> sentinel_t { return iter_end_; }
};

}  // namespace gviz

#endif  // GVIZARD_VIEWS_HPP_
