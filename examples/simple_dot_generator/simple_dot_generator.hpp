#ifndef SIMPLE_DOT_GENERATOR_HPP_
#define SIMPLE_DOT_GENERATOR_HPP_

#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <variant>

#include "gvizard/attrtypes/color.hpp"
#include "gvizard/gvizgraph.hpp"
#include "gvizard/utils.hpp"
#include "gvizard/colors/color.hpp"

#include "gvizard/attrs/label_related.hpp"
#include "gvizard/attrs/style.hpp"

struct NodeName final { std::string str; };

class SimpleDotGenerator final {
  constexpr static const char *str_indent = "    "; // 4 spaces

  // supported attributes, just for demonstration
  using attribte_variant_type =
    std::variant<gviz::attrs::Label, gviz::attrs::Style>;

 public:
  SimpleDotGenerator() {}

  auto generate(const gviz::GvizGraph<>& graph) const
  {
    std::stringstream strstream{};

    strstream << (graph.is_undirected() ? "graph" : "digraph") << " {\n";

    for (auto node_id : graph.graph.nodes_view()) {
      auto node_name =
          graph.graph.template get_entity_attr<NodeName>(node_id);
      if (!node_name) continue;

      strstream << str_indent;
      strstream << node_name->str;

      auto label = graph.get_node_label(node_id);
      auto style = graph.get_node_style(node_id);

      if (label || style) {
        strstream << " [";

        if (label) strstream << node_attr_to_string(*label)
                             << (style ? " " : "");
        if (style) strstream << node_attr_to_string(*style);

        strstream << "];";
      }

      strstream << '\n';
    }

    for (auto edge_id : graph.graph.edges_view()) {
      auto [node_a_id, node_b_id] = *graph.graph.get_edge_nodes(edge_id);

      auto node_a_name =
          graph.graph.template get_entity_attr<NodeName>(node_a_id);
      if (!node_a_name) continue;

      auto node_b_name =
          graph.graph.template get_entity_attr<NodeName>(node_b_id);
      if (!node_b_name) continue;

      // format: "   {node_a_name} {-- or ->} {node_b_name}\n"
      strstream << str_indent << node_a_name->str << ' '
                << (graph.is_undirected() ? "--" : "->")
                << ' ' << node_b_name->str << '\n';
    }

    strstream << "}";

    return strstream.str();
  }

 private:
  std::string node_attr_to_string(const attribte_variant_type& attr) const
  {
    auto [key, value] = node_attr_to_string_pair(attr);
    return key + "=" + value;
  }

  std::pair<std::string, std::string>
  node_attr_to_string_pair(const attribte_variant_type& attr) const
  {
    auto visitor = gviz::utils::LambdaVisitor{
      [](const gviz::attrs::Label& label) {
        return std::pair<std::string, std::string>(
          label.get_name(),
          std::string("\"") + label.get_value().get_format() + "\""
        );
      },
      [](const gviz::attrs::Style& style) {
        return std::pair<std::string, std::string>(
          style.get_name(),
          "dotted"
          //style.get_value().to_style_item_vector()[0].name
        );
      }
    };

    return std::visit(visitor, attr);
  }
};

#endif  // SIMPLE_DOT_GENERATOR_HPP_
