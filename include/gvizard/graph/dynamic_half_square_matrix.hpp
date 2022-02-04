#ifndef GVIZARD_GRAPH_DYNAMIC_HALF_SQUARE_MATRIX_HPP_
#define GVIZARD_GRAPH_DYNAMIC_HALF_SQUARE_MATRIX_HPP_

#include <cstddef>
#include <cmath>
#include <iterator>
#include <optional>
#include <utility>
#include <vector>

#include "gvizard/utils.hpp"

namespace gviz::detail {

/** A Dynamically Allocated Only-Square-Shape Half/Top-Triangle Matrix-like
 *  data structure that is suitable for resizing so much
 *  and undirected adjacency-matrix graph.
 *
 *  NOTE: its linear indexing is different, see `index` private function.
 */
template <typename T, typename Vector = std::vector<T>>
class DynamicHalfSquareMatrix {
  Vector      vec_{};
  std::size_t size_ = 0;

 public:
  using value_type = T;

  constexpr explicit DynamicHalfSquareMatrix() {}
  constexpr explicit DynamicHalfSquareMatrix(std::size_t n, T value = T())
  {
    resize(n, std::move(value));
  }

  constexpr std::size_t size() const noexcept { return size_; }

  constexpr void resize(std::size_t n, T value = T())
  {
    vec_.resize(tsize(n), std::move(value));
    size_ = n;
  }

  constexpr T& at(std::size_t n, std::size_t m)
  {
    // commented out the whole class is internal.
    // assert(size() <= n || n <= m);

    return vec_[index(n, m)];
  }

  constexpr const T& at(std::size_t n, std::size_t m) const
  {
    // commented out the whole class is internal.
    // assert(size() <= n || n <= m);

    return vec_[index(n, m)];
  }

  constexpr void add_rowcol(std::size_t count, T value = T())
  {
    resize(size() + count, std::move(value));
  }

  constexpr void pop_rowcol(std::size_t x)
  {
    if (size() == 0) return;

    std::size_t base = index(x, 0); // tsize(x)
    std::size_t delcount = size() - 1;
    std::size_t end = vec_.size() - delcount;

    std::size_t srcidx = index(x+1, 0); // tsize(x+1)
    std::size_t n = x+1; // current column

    for (std::size_t dstidx = base; dstidx < end; ++dstidx) {
      // skip index(n, x), the deleted element in row
      srcidx += srcidx == index(n, x);

      // TODO skip this edge case somehow else outside the loop...
      if (n != 1 || x != 0)
        vec_[dstidx] = std::move(vec_[srcidx]);

      n += dstidx >= index(n, 0); // tsize(n)
      ++srcidx;
    }

    resize(size() - 1);
  }

  // the iteration order won't be same as other matrices...
  // idx != (i * width + j)

  constexpr auto begin() { return std::begin(vec_); }
  constexpr auto end()   { return std::end(vec_);   }

  constexpr const auto cbegin() const { return std::cbegin(vec_); }
  constexpr const auto cend()   const { return std::cend(vec_);   }

  constexpr auto operator()(std::size_t n, std::size_t m)
  {
    return at(n, m);
  }

  constexpr auto operator()(std::size_t n, std::size_t m) const
  {
    return at(n, m);
  }

 private:
  constexpr std::size_t tsize(std::size_t n) const noexcept
  {
    return n * (n - 1) / 2;
  }

  constexpr std::size_t index(std::size_t n, std::size_t m) const noexcept
  {
    // assert(n > m);
    return n * (n - 1) / 2 + m;
  }

  constexpr auto reverse_index(std::size_t idx) const noexcept
    -> std::pair<std::size_t, std::size_t>
  {
    const std::size_t n = (std::sqrt(1 + 8*idx) - 1) / 2;
    return {n, idx - (n*(n-1))/2};
  }
};

}  // namespace gviz::detail

#endif  // GVIZARD_GRAPH_DYNAMIC_HALF_SQUARE_MATRIX_HPP_
