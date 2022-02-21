#include <catch2/catch.hpp>

#include <gvizard/attrtypes/addible.hpp>

using gviz::attrtypes::AddDouble;

TEST_CASE("[AddDouble] primary operators")
{
  AddDouble a = 3;
  AddDouble b = 4;

  REQUIRE(a + b == 7);
  REQUIRE(a - b == -1);
  REQUIRE(a * b == 12);
  REQUIRE(a / b == 3.0/4.0);
  REQUIRE(a / b != 1.0);

  REQUIRE( 7 == a + b);
  REQUIRE(-1 == a - b);
  REQUIRE(12 == a * b);
  REQUIRE(3.0/4.0 == a / b);
  REQUIRE(1.0 != a / b);

  REQUIRE(a != b);
}
