#include <cstddef>
#include <utility>

#include <catch2/catch.hpp>

#include <gvizard/graph/graph.hpp>
#include <gvizard/registry/entt_registry.hpp>

using namespace gviz;

TEST_CASE("[graph::Graph::undirected]")
{
  using Graph =
    graph::Graph<registry::EnTTRegistry, graph::GraphDir::undirected>;

  Graph graph;

  auto cluster_a = graph.create_cluster();
  auto cluster_b = graph.create_cluster();

  auto node_a = graph.create_node();
  auto node_b = graph.create_node();

  auto opt_node_c = graph.create_node_in(cluster_a);
  auto opt_node_d = graph.create_node_in(cluster_b);

  REQUIRE(opt_node_c.has_value());
  REQUIRE(opt_node_d.has_value());

  auto node_c = *opt_node_c;
  auto node_d = *opt_node_d;

  auto edge_a_b = graph.create_edge(node_a, node_b).value();
  auto edge_c_d = graph.create_edge(node_c, node_d).value();
  auto edge_a_d = graph.create_edge(node_a, node_d).value();

  SECTION("entity ids of each type shouldn't overlap (equal to each other)")
  {
    REQUIRE(cluster_a != cluster_b);

    REQUIRE(node_a != node_b);
    REQUIRE(node_b != node_c);
    REQUIRE(node_c != node_d);

    REQUIRE(edge_a_b != edge_c_d);
    REQUIRE(edge_c_d != edge_a_d);

    REQUIRE(node_a != edge_a_b);
    REQUIRE(node_a != cluster_a);
  }


  SECTION("create_edge returns same entity id if edge exists")
  {
    // if exists, must return same id...
    // must reorder when undirected... thus exists and must return same id...
    REQUIRE(edge_a_b == graph.create_edge(node_a, node_b).value());
    REQUIRE(edge_c_d == graph.create_edge(node_c, node_d).value());
    REQUIRE(edge_a_d == graph.create_edge(node_a, node_d).value());
  }

  if constexpr (graph.is_undirected_graph()) {
    SECTION("create_edge returns same id for same pair of nodes in any order")
    {
      REQUIRE(edge_a_b == graph.create_edge(node_b, node_a).value());
      REQUIRE(edge_c_d == graph.create_edge(node_d, node_c).value());
      REQUIRE(edge_a_d == graph.create_edge(node_d, node_a).value());
    }
  }

  //Graph::ClusterId clusters[] = { cluster_a, cluster_b };
  Graph::NodeId    nodes[] = { node_a, node_b, node_c, node_d };
  Graph::EdgeId    edges[] = { edge_a_b, edge_c_d, edge_a_d };

  std::pair<Graph::NodeId, Graph::NodeId> node_pairs[] = {
    {node_a, node_b}, {node_c, node_d}, {node_a, node_d}
  };

  SECTION("check created clusters against clusters_view")
  {
    for (const auto cluster_id : graph.clusters_view()) {
      bool is_a_or_b = cluster_id == cluster_a || cluster_id == cluster_b;
      REQUIRE(is_a_or_b);
    }
  }

  SECTION("check created nodes against nodes_view")
  {
    for (auto local_node_id : nodes) {
      bool is_found = false;
      for (const auto graph_node_id : graph.nodes_view())
        if (graph_node_id == local_node_id) {
          is_found = true;
          break;
        }

      REQUIRE(is_found);
    }
  }

  SECTION("check created edges against edges_view")
  {
    for (auto local_edge_id : edges) {
      bool is_found = false;
      for (const auto graph_edge_id : graph.edges_view())
        if (graph_edge_id == local_edge_id) {
          is_found = true;
          break;
        }

      REQUIRE(is_found);
    }
  }

  SECTION("check get_edge_nodes")
  {
    for (const auto edge_id : edges) {
      const auto [local_node_a, local_node_b] = *graph.get_edge_nodes(edge_id);
      bool is_found = false;
      for (const auto& [pair_a, pair_b] : node_pairs)
        if (pair_a == local_node_b && pair_b == local_node_a) {
          is_found = true;
          break;
        }

      REQUIRE(is_found);
    }
  }

  SECTION("check get_cluster_nodes")
  {
    // cluster_a

    auto view_a = graph.get_cluster_nodes(cluster_a);
    auto iter_a = view_a.begin();

    REQUIRE(bool(iter_a));
    REQUIRE(*iter_a == node_c);
    ++iter_a;
    REQUIRE(bool(iter_a == view_a.end()));
    REQUIRE_FALSE(iter_a.has_value());

    // cluster_b

    auto view_b = graph.get_cluster_nodes(cluster_b);
    auto iter_b = view_b.begin();

    REQUIRE(bool(iter_b));
    REQUIRE(*iter_b == node_d);
    ++iter_b;
    REQUIRE(bool(iter_b == view_b.end()));
    REQUIRE_FALSE(iter_b.has_value());
  }
}
