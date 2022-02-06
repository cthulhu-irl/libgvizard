#include <iostream>

#include <gvizard/gvizgraph.hpp>
#include <gvizard/attrtypes/label.hpp>
#include <gvizard/attrtypes/style.hpp>

#include "simple_dot_generator.hpp"

auto make_graph()
{
  gviz::GvizGraph<> ret{};

  auto node_a = ret.graph.create_node();
  auto node_b = ret.graph.create_node();
  auto node_c = ret.graph.create_node();
  auto node_d = ret.graph.create_node();

  ret.graph.set_entity_attr<NodeName>(node_a, NodeName{"a"});
  ret.graph.set_entity_attr<NodeName>(node_b, NodeName{"b"});
  ret.graph.set_entity_attr<NodeName>(node_c, NodeName{"c"});
  ret.graph.set_entity_attr<NodeName>(node_d, NodeName{"d"});

  ret.graph.create_edge(node_a, node_b);
  ret.graph.create_edge(node_c, node_d);

  ret.set_node_label(node_a, gviz::attrtypes::Label<>("This is Node A"));
  ret.set_node_label(node_a, gviz::attrtypes::Label<>("This is Node D"));

  ret.set_node_style(node_a, gviz::attrtypes::CommonStyle::bold);
  ret.set_node_style(node_b, gviz::attrtypes::CommonStyle::dashed);
  ret.set_node_style(node_c, gviz::attrtypes::CommonStyle::dotted);

  return ret;
}

int main()
{
  SimpleDotGenerator dotgenerator{};

  std::cout << dotgenerator.generate(make_graph()) << std::endl;

  return 0;
}
