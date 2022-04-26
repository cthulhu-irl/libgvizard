#ifndef GVIZARD_GVIZGRAPH_HPP_
#define GVIZARD_GVIZGRAPH_HPP_

#include <utility>

#include "gvizard/attrtypes/label.hpp"
#include "gvizard/attrtypes/style.hpp"
#include "gvizard/graph/graph.hpp"
#include "gvizard/registry/entt_registry.hpp"
#include "gvizard/registry/registry_entity_proxy.hpp"

#include "gvizard/attrs/label_related.hpp"
#include "gvizard/attrs/fillcolor.hpp"
#include "gvizard/attrs/style.hpp"

namespace gviz {

template <typename Graph = graph::Graph<registry::EnTTRegistry>>
struct GvizGraph {
 public:
  using registry_type = typename Graph::registry_type;
  using entity_type   = typename Graph::entity_type;

  using NodeId        = typename Graph::NodeId;
  using EdgeId        = typename Graph::EdgeId;
  using ClusterId     = typename Graph::ClusterId;

  Graph graph;

  registry::RegistryEntityProxy<registry_type> global_node_attrs;
  registry::RegistryEntityProxy<registry_type> global_edge_attrs;
  registry::RegistryEntityProxy<registry_type> global_cluster_attrs;

  constexpr GvizGraph(Graph graph_arg = {})
    : graph(std::move(graph_arg))
    , global_node_attrs(
                graph.get_raw_registry(), graph.get_raw_registry().create())
    , global_edge_attrs(
                graph.get_raw_registry(), graph.get_raw_registry().create())
    , global_cluster_attrs(
                graph.get_raw_registry(), graph.get_raw_registry().create())
  {}

  constexpr bool is_directed()   const { return graph.is_directed();   }
  constexpr bool is_undirected() const { return graph.is_undirected(); }

  // get attribute helper methods

  auto get_node_label(NodeId node_id) const
  {
    return graph.template get_entity_attr<attrs::Label>(node_id);
  }

  auto get_node_style(NodeId node_id) const
  {
    return graph.template get_entity_attr<attrs::Style>(node_id);
  }

  // set attribute helper methods

  void set_node_label(NodeId node_id, attrtypes::Label<> label)
  {
    graph.template set_entity_attr<attrs::Label>(node_id, std::move(label));
  }

  void set_node_style(NodeId node_id, attrtypes::Style style)
  {
    graph.template set_entity_attr<attrs::Style>(node_id, std::move(style));
  }
};

};

#endif  // GVIZARD_GVIZGRAPH_HPP_
