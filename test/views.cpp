#include <iterator>
#include <vector>
#include <optional>

#include <catch2/catch.hpp>

#include <gvizard/views.hpp>

using gviz::IteratorView;
using gviz::CallbackView;

TEST_CASE("[IteratorView]")
{
  std::vector<int> v   = { 1, 2, 3, 4,  5  };
  const int        u[] = { 1, 4, 9, 16, 25 };

  IteratorView<decltype(v)> iter_v(v.begin(), v.end());
  IteratorView<decltype(u)> iter_u(std::begin(u), std::end(u));

  int i = 0;
  for (auto val : iter_v) {
    REQUIRE(val == (i+1));
    REQUIRE(val*val == u[i]);
    ++i;
  }
}

TEST_CASE("[CallbackView] with init value")
{
  constexpr auto callback = [end=10](int i) -> std::optional<int> {
    if (i >= end) return std::nullopt;
    else          return i+1;
  };

  auto iter = CallbackView<int, decltype(callback)>(callback, 0);

  int i = 0;
  for (auto val : iter) {
    REQUIRE(val == i);
    ++i;
  }
}

TEST_CASE("[CallbackView] without init value")
{
  const int arr[] = { 0, 1, 4, 9, 16 };

  auto callback =
    [iter=std::begin(arr), end=std::end(arr)](int) mutable
      -> std::optional<int>
    {
      if (iter == end) return std::nullopt;
      auto val = *iter;
      ++iter;
      return val;
    };

  auto iter = CallbackView<int, decltype(callback)>(callback);

  int i = 0;
  for (auto val : iter) {
    REQUIRE(val == (i*i));
    ++i;
  }
}
