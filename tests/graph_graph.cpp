#include <catch2/catch.hpp>
#include <cstddef>
#include <fmt/core.h>

#include <gvizard/graph/graph.hpp>
#include <gvizard/registry/entt_registry.hpp>
#include <utility>

using namespace gviz;

TEST_CASE("[Graph:undirected]")
{
  using Graph =
    graph::Graph<registry::EnTTRegistry, graph::GraphDir::undirected>;

  Graph graph;

  auto cluster_a = graph.create_cluster();
  auto cluster_b = graph.create_cluster();

  auto node_a = graph.create_node();
  auto node_b = graph.create_node();
  auto node_c = graph.create_node_in(cluster_a);
  auto node_d = graph.create_node_in(cluster_b);

  auto edge_a_b = graph.create_edge(node_a, node_b).value();
  auto edge_c_d = graph.create_edge(node_c, node_d).value();
  auto edge_a_d = graph.create_edge(node_a, node_d).value();

  REQUIRE(cluster_a != cluster_b);

  REQUIRE(node_a != node_b);
  REQUIRE(node_b != node_c);
  REQUIRE(node_c != node_d);

  REQUIRE(edge_a_b != edge_c_d);
  REQUIRE(edge_c_d != edge_a_d);

  REQUIRE(node_a != cluster_a);

  Graph::ClusterId clusters[] = { cluster_a, cluster_b };
  Graph::NodeId    nodes[] = { node_a, node_b, node_c, node_d };
  Graph::EdgeId    edges[] = { edge_a_b, edge_c_d, edge_a_d };

  std::pair<Graph::NodeId, Graph::NodeId> node_pairs[] = {
    {node_a, node_b}, {node_c, node_d}, {node_a, node_d}
  };

  SECTION("check created clusters against clusters_view") {
    for (const auto cluster_id : graph.clusters_view()) {
      bool is_a_or_b = cluster_id == cluster_a || cluster_id == cluster_b;
      REQUIRE(is_a_or_b);
    }
  }

  SECTION("check created nodes against nodes_view") {
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

  SECTION("check created edges against edges_view") {
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

  SECTION("check get_edge_nodes") {
    for (const auto edge_id : edges) {
      const auto [local_node_a, local_node_b] = *graph.get_edge_nodes(edge_id);
      bool is_found = false;
      for (const auto [pair_a, pair_b] : node_pairs)
        if (pair_a == local_node_b && pair_b == local_node_a) {
          is_found = true;
          break;
        }

      REQUIRE(is_found);
    }
  }
}
