#include <memory>
#include <optional>

#include <catch2/catch.hpp>

#include <gvizard/utils.hpp>

using gviz::utils::OptionalRef;

TEST_CASE("[OptionalRef] basic value functionalities")
{
  int num = 12;
  std::optional<int> opt_num_val = num;
  std::optional<int> opt_num_null = std::nullopt;

  OptionalRef<std::optional<int>> optref_null = gviz::utils::nulloptref;
  OptionalRef<std::optional<int>> optref_optnull = opt_num_null;
  OptionalRef<std::optional<int>> optref_optval = opt_num_val;

  OptionalRef<std::optional<int>> optref_null_copy = optref_null;
  OptionalRef<std::optional<int>> optref_optnull_copy = optref_optnull;
  OptionalRef<std::optional<int>> optref_optval_copy = optref_optval;

  REQUIRE(!optref_null);
  REQUIRE(optref_optnull);
  REQUIRE(optref_optval);

  REQUIRE(optref_optnull.value() == opt_num_null);
  REQUIRE(optref_optval.value() == opt_num_val);

  REQUIRE_FALSE(optref_null.has_value());
  REQUIRE(optref_optnull.has_value());
  REQUIRE(optref_optval.has_value());

  REQUIRE(optref_null.value_or(42) == 42);
  REQUIRE(optref_optnull.value_or(42) == opt_num_null);
  REQUIRE(optref_optval.value_or(42) == opt_num_val);

  REQUIRE(optref_null == nullptr);
  REQUIRE(optref_optnull == std::addressof(opt_num_null));
  REQUIRE(optref_optval == std::addressof(opt_num_val));

  REQUIRE_FALSE(optref_optnull->has_value());
  REQUIRE(optref_optval->has_value());
}
