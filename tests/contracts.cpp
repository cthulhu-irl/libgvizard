#include <catch2/catch_all.hpp>

#include <gvizard/contracts.hpp>

static constexpr auto unsigned_int_pred = +[](int v) { return v >= 0; };

using gviz::contracts::Contract;

using unsigned_int = Contract<int, unsigned_int_pred>;

TEST_CASE("[Contract] assignment assurance")
{
  unsigned_int a = 12;

  REQUIRE(a == 12);

  REQUIRE_NOTHROW(a = 1);

  REQUIRE_THROWS(a = -1);

  REQUIRE(a.assign(1));
  REQUIRE_FALSE(a.assign(-1));

  REQUIRE(a.check(1));
  REQUIRE_FALSE(a.check(-1));
}

TEST_CASE("[Contract] operators")
{
  unsigned int e = 11;
  unsigned_int a = 12;
  unsigned_int b = 13;
  unsigned_int c = a;
  unsigned int d = a;

  REQUIRE(a != b);
  REQUIRE(a == c);
  REQUIRE(a == d);

  REQUIRE(a < b);
  REQUIRE(a <= b);
  REQUIRE(c <= a);
  REQUIRE(e <= a);
  REQUIRE(e < a);

  REQUIRE(a > e);
  REQUIRE(a >= c);
  REQUIRE(a >= e);
  REQUIRE(b > a);

  REQUIRE(*a == 12);

  REQUIRE(a - 2 == 10);
  REQUIRE(a + 2 == 14);
  REQUIRE(a / 2 == 6);
  REQUIRE(a * 2 == 24);
  REQUIRE(a % 2 == 0);

  REQUIRE_FALSE(!a);

  REQUIRE((a & 1) == 0);
  REQUIRE((a | 1) == 13);

  // REQUIRE(++a == 13); // not supported
}
