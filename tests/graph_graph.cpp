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
    int i = 0;
    for (const auto cluster_id : graph.clusters_view()) {
      bool is_a_or_b = cluster_id == cluster_a || cluster_id == cluster_b;
      REQUIRE(is_a_or_b);
      ++i;
    }
    REQUIRE(i == 2);
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
    int i = 0;
    for (auto node_id : graph.get_cluster_nodes(cluster_a)) {
      REQUIRE(node_id == node_c);
      ++i;
    }
    REQUIRE(i == 1);

    i = 0;
    for (auto node_id : graph.get_cluster_nodes(cluster_b)) {
      REQUIRE(node_id == node_d);
      ++i;
    }
    REQUIRE(i == 1);

  }

  SECTION("check get_edges_of")
  {
    int i = 0;
    for (auto edge_id : graph.get_edges_of(node_a)) {
      bool is_ab_or_ad = edge_id == edge_a_b || edge_id == edge_a_d;
      REQUIRE(is_ab_or_ad);
      ++i;
    }
    REQUIRE(i == 2);
  }

  SECTION("check get_degree")
  {
    REQUIRE(graph.get_degree(node_a) == 2);
    REQUIRE(graph.get_degree(node_b) == 1);
    REQUIRE(graph.get_degree(node_c) == 1);
    REQUIRE(graph.get_degree(node_d) == 2);
  }

  SECTION("check get_edge_id")
  {
    REQUIRE(graph.get_edge_id(node_a, node_b) == edge_a_b);
    REQUIRE(graph.get_edge_id(node_c, node_d) == edge_c_d);
    REQUIRE(graph.get_edge_id(node_a, node_d) == edge_a_d);

    if constexpr (graph.is_undirected_graph()) { // check in reverse order.
      REQUIRE(graph.get_edge_id(node_b, node_a) == edge_a_b);
      REQUIRE(graph.get_edge_id(node_d, node_c) == edge_c_d);
      REQUIRE(graph.get_edge_id(node_d, node_a) == edge_a_d);
    }

    REQUIRE_FALSE(graph.get_edge_id(node_a, node_c).has_value());
    REQUIRE_FALSE(graph.get_edge_id(node_d, node_b).has_value());
    REQUIRE_FALSE(graph.get_edge_id(node_c, node_a).has_value());
    REQUIRE_FALSE(graph.get_edge_id(node_b, node_d).has_value());
  }

  // add_to_cluster as preparation for modifier methods.
  auto node_other = graph.create_node();
  auto cluster_other = graph.create_cluster();
  REQUIRE(graph.add_to_cluster(cluster_other, node_other));
  REQUIRE(graph.get_node_cluster(node_other) == cluster_other);

  SECTION("check detach_clustered_node")
  {
    REQUIRE(graph.detach_clustered_node(node_other));

    // must return false for unattached nodes.
    REQUIRE_FALSE(graph.detach_clustered_node(node_a));
    REQUIRE_FALSE(graph.detach_clustered_node(node_other));
  }

  // TODO implement these?
  //
  // remove_node
  // remove_edge
  // remove_cluster
  //
  // node_count
  // edge_count
  // cluster_count
}
