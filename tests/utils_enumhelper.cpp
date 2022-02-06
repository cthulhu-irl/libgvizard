#include <cstdint>

#include <catch2/catch.hpp>

#include <gvizard/utils.hpp>

using gviz::utils::EnumHelper;

enum class EdgeDir : uint8_t { in = 1, out = 2, inout = 3 };

TEST_CASE("[EnumHelper] basic functionalities")
{
  REQUIRE(EnumHelper<EdgeDir>::from_index(0) == EdgeDir::in);
  REQUIRE(EnumHelper<EdgeDir>::from_index(1) == EdgeDir::out);
  REQUIRE(EnumHelper<EdgeDir>::from_index(2) == EdgeDir::inout);

  REQUIRE(EnumHelper<EdgeDir>::from_value(1) == EdgeDir::in);
  REQUIRE(EnumHelper<EdgeDir>::from_value(2) == EdgeDir::out);
  REQUIRE(EnumHelper<EdgeDir>::from_value(3) == EdgeDir::inout);

  REQUIRE(EnumHelper<EdgeDir>::to_str(EdgeDir::in) == "in");
  REQUIRE(EnumHelper<EdgeDir>::to_str(EdgeDir::out) == "out");
  REQUIRE(EnumHelper<EdgeDir>::to_str(EdgeDir::inout) == "inout");

  REQUIRE(EnumHelper<EdgeDir>::from_str("in") == EdgeDir::in);
  REQUIRE(EnumHelper<EdgeDir>::from_str("out") == EdgeDir::out);
  REQUIRE(EnumHelper<EdgeDir>::from_str("inout") == EdgeDir::inout);

  REQUIRE(EnumHelper<EdgeDir>::from_index(4) == std::nullopt);
  REQUIRE(EnumHelper<EdgeDir>::from_value(0) == std::nullopt);
  REQUIRE(EnumHelper<EdgeDir>::from_value(4) == std::nullopt);
  REQUIRE(EnumHelper<EdgeDir>::from_str("invalid") == std::nullopt);
}
