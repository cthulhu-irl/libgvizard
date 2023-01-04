#include <string>

#include <catch2/catch_all.hpp>

#include <gvizard/registry/entt_registry.hpp>
#include <gvizard/registry/registry_entity_proxy.hpp>

using gviz::registry::EnTTRegistry;
using gviz::registry::RegistryEntityProxy;

struct Name { std::string str; };

TEST_CASE("[registry::EnTTRegistry]")
{
  EnTTRegistry registry{};

  auto a = registry.create();
  auto b = registry.create();

  auto a_name = registry.set<Name>(a, "entity a");
  auto b_name = registry.set<Name>(b, "entity b");

  auto a_num = registry.emplace<std::size_t>(a, 12);
  auto b_num = registry.emplace<std::size_t>(b, 42);

  REQUIRE(a_name);
  REQUIRE(b_name);
  REQUIRE(a_name->str == "entity a");
  REQUIRE(b_name->str == "entity b");

  REQUIRE(a_num);
  REQUIRE(b_num);
  REQUIRE(*a_num == 12);
  REQUIRE(*b_num == 42);

  REQUIRE(a_name == registry.get<Name>(a));
  REQUIRE(b_name == registry.get<Name>(b));

  REQUIRE(a_name == registry.get<std::size_t>(a));
  REQUIRE(b_name == registry.get<std::size_t>(b));

  REQUIRE(registry.size() == 2);

  auto updated =
    registry.update<std::size_t>(a, [](auto& num) { return num *= 2; });

  REQUIRE(updated);
  REQUIRE(*registry.get<std::size_t>(a) == 24);

  REQUIRE(registry.remove<Name>(b));

  REQUIRE_FALSE(registry.get<float>(a));
  REQUIRE_FALSE(registry.get<Name>(b));
  REQUIRE_FALSE(registry.update<Name>(b, [](const auto&) { return ""; }));
  REQUIRE_FALSE(registry.remove<Name>(b));

  registry.destroy(b);
  REQUIRE(registry.size() == 1);
}

TEST_CASE("[registry::RegistryEntityProxy]")
{
  EnTTRegistry registry{};

  auto entity_id = registry.create();

  RegistryEntityProxy<EnTTRegistry> entity(registry, entity_id);

  auto e_name = entity.set<Name>("entity");
  auto e_num  = entity.set<std::size_t>(std::size_t(42));

  REQUIRE(e_name);
  REQUIRE_FALSE(entity.get<float>());

  REQUIRE(e_name == entity.get<Name>());
  REQUIRE(e_num  == entity.get<std::size_t>());

  auto updated =
    entity.update<std::size_t>([](auto& num) { num *= 2; });

  REQUIRE(updated);
  REQUIRE(*entity.get<std::size_t>() == 84);

  REQUIRE(entity.remove<Name>());

  REQUIRE_FALSE(entity.get<Name>());
  REQUIRE_FALSE(entity.update<Name>([](const auto&) {}));
  REQUIRE_FALSE(entity.remove<Name>());
}

