#include <catch2/catch.hpp>

#include <gvizard/graph/dynamic_square_matrix.hpp>
#include <gvizard/graph/dynamic_half_square_matrix.hpp>

using gviz::detail::DynamicSquareMatrix;
using gviz::detail::DynamicHalfSquareMatrix;

TEST_CASE("[graph::detail::DynamicSquareMatrix]")
{
  constexpr std::size_t size = 5;
  constexpr auto index =
    [](std::size_t i, std::size_t j) { return j * size + i; };

  DynamicSquareMatrix<int> matrix(size);
  int arr[] = {
     1,  2,  3,  4,  5,
     6,  7,  8,  9, 10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20,
    21, 22, 23, 24, 25
  };

  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < size; ++j)
      matrix(i, j) = arr[index(i, j)];

  // --

  REQUIRE(matrix.size() == size);

  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < size; ++j)
      REQUIRE(matrix.at(i, j) == arr[index(i, j)]);

  // --

  matrix.pop_rowcol(3);

  REQUIRE(matrix.size() == (size-1));

  for (std::size_t i = 0; i < (size-1); ++i)
    for (std::size_t j = 0; j < (size-1); ++j) {
      const auto n = (i == 3) ? (i+1) : i;
      const auto m = (j == 3) ? (j+1) : j;
      REQUIRE(matrix.at(i, j) == arr[index(n, m)]);
    }

  // --

  matrix.pop_rowcol(3);

  REQUIRE(matrix.size() == (size-2));

  for (std::size_t i = 0; i < (size-2); ++i)
    for (std::size_t j = 0; j < (size-2); ++j)
      REQUIRE(matrix.at(i, j) == arr[index(i, j)]);

  // --

  matrix.add_rowcol(2, 42);

  REQUIRE(matrix.size() == size);

  for (std::size_t i = 0; i < (size-1); ++i)
    for (std::size_t j = 0; j < (size-1); ++j) {
      const auto expected = (i < 3 && j < 3) ? arr[index(i, j)] : 42;
      REQUIRE(matrix.at(i, j) == expected);
    }
}

TEST_CASE("[graph::detail::DynamicHalfSquareMatrix]")
{
  constexpr std::size_t size = 5;
  constexpr auto index =
    [](std::size_t i, std::size_t j) { return j * size + i; };

  constexpr int Z = 0;

  DynamicHalfSquareMatrix<int> matrix(size);
  int arr[] = {
     Z,  2,  3,  4,  5,
     Z,  Z,  8,  9, 10,
     Z,  Z,  Z, 14, 15,
     Z,  Z,  Z,  Z, 20,
     Z,  Z,  Z,  Z,  Z
  };

  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < i; ++j)
      matrix(i, j) = arr[index(i, j)];

  // --

  REQUIRE(matrix.size() == size);

  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < i; ++j)
      REQUIRE(matrix.at(i, j) == arr[index(i, j)]);

  // --

  matrix.pop_rowcol(3);

  REQUIRE(matrix.size() == (size-1));

  for (std::size_t i = 0; i < (size-1); ++i)
    for (std::size_t j = 0; j < i; ++j) {
      const auto n = (i == 3) ? (i+1) : i;
      const auto m = (j == 3) ? (j+1) : j;
      REQUIRE(matrix.at(i, j) == arr[index(n, m)]);
    }

  // --

  matrix.pop_rowcol(3);

  REQUIRE(matrix.size() == (size-2));

  for (std::size_t i = 0; i < (size-2); ++i)
    for (std::size_t j = 0; j < i; ++j)
      REQUIRE(matrix.at(i, j) == arr[index(i, j)]);

  // --

  matrix.add_rowcol(2, 42);

  REQUIRE(matrix.size() == size);

  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < i; ++j) {
      const auto expected = (i < 3 && j < 3) ? arr[index(i, j)] : 42;
      REQUIRE(matrix.at(i, j) == expected);
    }
}
