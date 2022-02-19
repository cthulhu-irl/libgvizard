#ifndef GVIZARD_GRAPH_GRAPH_HPP_
#define GVIZARD_GRAPH_GRAPH_HPP_

#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <optional>
#include <tuple>
#include <type_traits>
#include <map>
#include <utility>
#include <variant>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>

#include "gvizard/utils.hpp"

#include "gvizard/graph/dynamic_square_matrix.hpp"
#include "gvizard/graph/dynamic_half_square_matrix.hpp"

namespace gviz::graph {

struct no_view_t {};

enum class EntityTypeEnum { unknown, node, edge, cluster };

enum class GraphDir : int { undirected = 0, directed = 1 };
enum class EdgeDir  : int { in = 1, out = 2, inout = 3 };


/** an adjancency-matrix implementation of graph using registry for
 * id generation and attribute management, with support of clustering nodes.
 *
 * node, edge, and cluster are called entity.
 *
 * creating any kind of entity returns a unqiue id of type NodeId, EdgeId,
 * ClusterId respectively for node, edge, cluster.
 * using a removed id results in undefined behavior.
 *
 * NOTE: use proxy methods to get/set/emplace/remove an entity's attribute
 *       instead of get_raw_registry.
 */
template <typename Registry, GraphDir DirV = GraphDir::undirected>
class Graph {
 public:
  using entity_type = typename Registry::entity_type;

  using registry_type = Registry;

  using NodeId    = entity_type; /// always convertible to entity_type
  using EdgeId    = entity_type; /// always convertible to entity_type
  using ClusterId = entity_type; /// always convertible to entity_type

 private:
  struct NodeItem final {
    std::size_t              idx;
    std::optional<ClusterId> cluster_id = std::nullopt;
  };

  struct EdgeItem final {
    std::size_t n;
    std::size_t m;

    NodeId node_a_id;
    NodeId node_b_id;
  };

  struct ClusterItem final {};

  class Item final {
    EntityTypeEnum type_;
    union {
      NodeItem    node_;
      EdgeItem    edge_;
      ClusterItem cluster_;
    };

   public:
    Item() : type_(EntityTypeEnum::unknown) {}

    constexpr Item(NodeItem node) noexcept
      : type_(EntityTypeEnum::node), node_(std::move(node))
    {}

    constexpr Item(EdgeItem edge) noexcept
      : type_(EntityTypeEnum::edge), edge_(std::move(edge))
    {}

    constexpr Item(ClusterItem cluster) noexcept
      : type_(EntityTypeEnum::cluster), cluster_(std::move(cluster))
    {}

    constexpr EntityTypeEnum type() const noexcept { return type_; }

    constexpr bool is_node() const noexcept
    {
      return type_ == EntityTypeEnum::node;
    }

    constexpr bool is_edge() const noexcept
    {
      return type_ == EntityTypeEnum::edge;
    }

    constexpr bool is_cluster() const noexcept
    {
      return type_ == EntityTypeEnum::cluster;
    }

    constexpr       NodeItem& as_node()       { return node_; }
    constexpr const NodeItem& as_node() const { return node_; }

    constexpr       EdgeItem& as_edge()       { return edge_; }
    constexpr const EdgeItem& as_edge() const { return edge_; }

    constexpr       ClusterItem& as_cluster()       { return cluster_; }
    constexpr const ClusterItem& as_cluster() const { return cluster_; }
  };

 private:
  constexpr static bool is_undirected = DirV == GraphDir::undirected;

  using optional_entity_type = std::optional<entity_type>;

  using matrix_type =
    std::conditional_t<
      is_undirected,
      detail::DynamicSquareMatrix<optional_entity_type>,
      detail::DynamicHalfSquareMatrix<optional_entity_type>
    >;
  using map_type = std::map<entity_type, Item>;

  matrix_type   matrix_{};
  map_type      entities_map_{};
  registry_type registry_{};

  std::size_t nodes_count_    = 0;
  std::size_t edges_count_    = 0;
  std::size_t clusters_count_ = 0;

 public:
  auto&       get_raw_registry()       { return registry_; }
  const auto& get_raw_registry() const { return registry_; }

  constexpr bool is_directed_graph() const { return !is_undirected; }
  constexpr bool is_undirected_graph() const { return is_undirected; }

  // registry attribute accessor/modifier methods

  /** get an `entity_id` entity's attribute `Attr`
   *
   * @returns an optional reference to `Attr` of `entity_id`
   *          if `entity_id` exists and `Attr` is set
   *          or otherwise `utils::nulloptref`.
   */
  template <typename Attr>
  auto get_entity_attr(entity_type entity_id) -> utils::OptionalRef<Attr>
  {
    return registry_.template get<Attr>(entity_id);
  }

  /** get an `entity_id` entity's attribute `Attr`
   *
   * @returns a const optional reference to `Attr` of `entity_id`
   *          if `entity_id` exists and `Attr` is set
   *          or otherwise `utils::nulloptref`.
   */
  template <typename Attr>
  auto get_entity_attr(entity_type entity_id) const
    -> utils::OptionalRef<const Attr>
  {
    return registry_.template get<Attr>(entity_id);
  }

  /** checks if `entity_id` is valid and has its attribute `Attr` set.
   *
   * @param entity_id entity's id.
   * @returns true if `entity_id` exists and `Attr` is set, otherwise false.
   */
  template <typename Attr>
  bool has_entity_attr(entity_type entity_id) const
  {
    return registry_.template has<Attr>(entity_id);
  }

  /** sets an entity's attribute if `entity_id` is valid.
   *
   * @param entity_id entity's id.
   * @param value the value to be set, it'll be converted to `Attr` explicitly.
   * @returns utils::nulloptref if `entity_id` is invalid, otherwise
   *          an optional reference to the residing `Attr` which was set
   *          in registry.
   */
  template <typename Attr, typename ValT>
  auto set_entity_attr(entity_type entity_id, ValT&& value)
    -> utils::OptionalRef<Attr>
  {
    return registry_.template set<Attr>(entity_id, std::forward<ValT>(value));
  }

  /** constructs an entity's attribute in-place
   *  by given `args` if `entity_id` is valid.
   *
   * @param entity_id entity's id.
   * @param args arguments to be passed to `Attr` constructor.
   * @returns utils::nulloptref if `entity_id` is invalid, otherwise
   *          an optional reference to the constructed `Attr` which was placed
   *          in registry.
   */
  template <typename Attr, typename ...Args>
  auto emplace_entity_attr(entity_type entity_id, Args&&... args)
    -> utils::OptionalRef<Attr>
  {
    return registry_.template emplace<Attr>(
      entity_id,
      std::forward<Args>(args)...
    );
  }

  /** unsets/removes `Attr` attribute of entity
   *  if `entity_id` is valid and has `Attr`.
   *
   * @param entity_id entity's id.
   * @param args arguments to be passed to `Attr` constructor.
   * @returns true if `entity_id` is valid or has `Attr`, otherwise false.
   */
  template <typename Attr>
  bool remove_entity_attr(entity_type entity_id)
  {
    return registry_.template remove<Attr>(entity_id);
  }

  // graph data structure methods

  /** creates a new cluster.
   *
   * @returns id of created cluster.
   */
  auto create_cluster() -> ClusterId
  {
    auto cluster_id = registry_.create();

    entities_map_[cluster_id] = ClusterItem{};

    return cluster_id;
  }

  /** adds a node to a cluster.
   *
   * if node was already in a cluster, it'll be detached and added to
   * given cluster.
   *
   * @param cluster_id target cluster's id to add node to.
   * @param node_id node's id to add to cluster.
   * @returns true if `cluster_id` and `node_id` are both valid,
   *          otherwise false.
   */
  bool add_to_cluster(ClusterId cluster_id, NodeId node_id)
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return false;

    const auto cluster_iter = entities_map_.find(cluster_id);
    if (cluster_iter == entities_map_.end() || !cluster_iter->second.is_cluster())
      return false;

    auto& node_item = node_iter->second.as_node();
    node_item.cluster_id = cluster_id;

    return true;
  }

  /** creates a new node.
   *
   * @returns id of the created node.
   */
  auto create_node() -> NodeId
  {
    auto node_id = registry_.create();
    const auto idx = matrix_.size();

    matrix_.add_rowcol(1, std::nullopt);
    entities_map_[node_id] = NodeItem{idx};

    return node_id;
  }

  /** creates a node in the given cluster.
   *
   * @param cluster_id cluster's id to create node in.
   * @returns an optional containing NodeId if `cluster_id` is valid,
   *          otherwise std::nullopt.
   */
  auto create_node_in(ClusterId cluster_id) -> std::optional<NodeId>
  {
    const auto cluster_iter = entities_map_.find(cluster_id);
    if (cluster_iter == entities_map_.end() || !cluster_iter->second.is_cluster())
      return std::nullopt;

    auto node_id = registry_.create();
    const auto idx = matrix_.size();

    matrix_.add_rowcol(1, std::nullopt);
    entities_map_[node_id] = NodeItem{idx, cluster_id};

    return node_id;
  }

  /** creates an edge between two given nodes.
   *
   * if graph is directed, first node is source and second is dest.
   *
   * if the same edge existed between these two nodes,
   * the id of existing edge will be returned.
   *
   * @param node_a_id first (or source) node's id.
   * @param node_b_id second (or dest) node's id.
   * @returns an optional containing EdgeId if both nodes' id are valid,
   *          otherwise std::nullopt.
   */
  auto create_edge(NodeId node_a_id, NodeId node_b_id)
    -> std::optional<EdgeId>
  {
    if constexpr (is_undirected)
      if (node_a_id == node_b_id)
        return std::nullopt;

    auto node_a_iter = entities_map_.find(node_a_id);
    if (node_a_iter == entities_map_.end() || !node_a_iter->second.is_node())
      return std::nullopt;

    auto node_b_iter = entities_map_.find(node_b_id);
    if (node_b_iter == entities_map_.end() || !node_b_iter->second.is_node())
      return std::nullopt;

    auto node_a_idx = node_a_iter->second.as_node().idx;
    auto node_b_idx = node_b_iter->second.as_node().idx;

    if constexpr (is_undirected) {
      // this must be ensured to be impossible in elsewhere.
      //if (node_a_idx == node_b_idx)
      //  return std::nullopt;

      // mirroring triangle
      if (node_a_idx < node_b_idx) {
        std::swap(node_a_id, node_b_id);
        std::swap(node_a_idx, node_b_idx);
      }
    }

    auto& opt_edge = matrix_.at(node_a_idx, node_b_idx);
    if (opt_edge) // is there already an edge?
      return *opt_edge;

    auto edge_id = registry_.create();

    entities_map_[edge_id] = EdgeItem{
      node_a_idx,
      node_b_idx,
      node_a_id,
      node_b_id
    };

    opt_edge = edge_id;

    return edge_id;
  }

  /** returns an iterable view to node ids of given cluster.
   *
   * @param cluster_id target cluster's id.
   * @returns an iterable view to cluster's nodes.
   *          if `cluster_id` is invalid, the view will be empty.
   */
  auto get_cluster_nodes(ClusterId cluster_id) const
  {
    return entities_map_
      | ranges::views::filter(
          [cluster_id=cluster_id](const auto& pair) {
            return pair.second.is_node() && pair.second.as_node().cluster_id == cluster_id;
          }
        )
      | ranges::views::transform([](const auto& pair) { return pair.first; });
  }

  /** retrieves given two nodes' edge.
   * direction is determined by order of given arguments.
   *
   * @param node_a_id first node's id.
   * @param node_b_id second node's id.
   * @returns an optional containing EdgeId if both nodes' id are valid
   *          and an edge (desired direction) is between them,
   *          otherwise std::nullopt.
   */
  auto get_edge_id(NodeId node_a_id, NodeId node_b_id) const
    -> std::optional<EdgeId>
  {
    if constexpr (is_undirected)
      if (node_a_id == node_b_id)
        return std::nullopt;

    auto node_a_iter = entities_map_.find(node_a_id);
    if (node_a_iter == entities_map_.end() || !node_a_iter->second.is_node())
      return std::nullopt;

    auto node_b_iter = entities_map_.find(node_b_id);
    if (node_b_iter == entities_map_.end() || !node_b_iter->second.is_node())
      return std::nullopt;

    auto node_a_idx = node_a_iter->second.as_node().idx;
    auto node_b_idx = node_b_iter->second.as_node().idx;

    if constexpr (is_undirected) {
      // this must be impossible by design.
      //if (node_a_idx == node_b_idx)
      //  return std::nullopt;

      if (node_a_idx <= node_b_idx)
        std::swap(node_a_idx, node_b_idx);
    }

    return matrix_.at(node_a_idx, node_b_idx);
  }

  /** retrieves given edge's pair of nodes.
   *
   * @param edge_id target edge's id.
   * @returns an optional containing a pair of NodeId if `edge_id` is valid,
   *          otherwise std::nullopt.
   */
  auto get_edge_nodes(EdgeId edge_id) const
    -> std::optional<std::pair<NodeId, NodeId>>
  {
    auto edge_iter = entities_map_.find(edge_id);
    if (edge_iter == entities_map_.end() || !edge_iter->second.is_edge())
      return std::nullopt;

    const auto node_a_id = edge_iter->second.as_edge().node_a_id;
    const auto node_b_id = edge_iter->second.as_edge().node_b_id;

    // order (node_a_idx > node_a_idx) must be ensured by design.
    return std::pair<NodeId, NodeId>{ node_a_id, node_b_id };
  }

  /** detaches given cluster's nodes from it, and then removes the cluster.
   *
   * @param cluster_id target cluster's id.
   * @returns true if `cluster_id` is valid, otherwise false.
   */
  bool remove_cluster(ClusterId cluster_id)
  {
    for (auto& [entity_id, item] : entities_map_) {
      if (item.is_node() && item.as_node().cluster_id)
        item.as_node().cluster_id = std::nullopt;
    }

    auto cluster_iter = entities_map_.find(cluster_id);
    if (cluster_iter == entities_map_.end() || !cluster_iter->second.is_cluster())
      return false;

    registry_.destroy(cluster_id);
    entities_map_.erase(cluster_id);

    --clusters_count_;

    return true;
  }

  /** removes a node.
   *
   * @param node_id target node's id.
   * @returns true if `node_id` is valid, otherwise false.
   */
  bool remove_node(NodeId node_id)
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return false;

    const auto node_item = node_iter->second.as_node();

    matrix_.pop_rowcol(node_item.idx);

    for (auto& [entity_id, item] : entities_map_) {
      if (item.is_node() && item.as_node().idx > node_item.idx)
        --item.as_node().idx;
    }

    registry_.destroy(node_id);
    entities_map_.erase(node_iter);

    --nodes_count_;

    return true;
  }

  /** detaches a node from its cluster if it is attached to one.
   *
   * @param node_id target node's id.
   * @returns true if `node_id` is valid, otherwise false.
   */
  bool detach_clustered_node(NodeId node_id)
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return false;

    node_iter->second.as_node().cluster_id = std::nullopt;

    return true;
  }

  /** removes an edge between given two nodes.
   *
   * if directed graph, first node is source and second is dest of the edge.
   *
   * @param node_a_id first (source) node's id.
   * @param node_b_id second (dest) node's id.
   * @returns true if both nodes' id are valid and an edge exists between,
   *          otherwise false.
   */
  bool remove_edge(NodeId node_a_id, NodeId node_b_id)
  {
    auto opt_edge_id = get_edge_id(node_a_id, node_b_id);
    if (!opt_edge_id)
      return false;

    auto edge_item = entities_map_[*opt_edge_id];

    matrix_.at(edge_item.n, edge_item.m) = std::nullopt;

    registry_.destroy(*opt_edge_id);
    entities_map_.erase(*opt_edge_id);

    --edges_count_;

    return true;
  }

  /** removes an edge by given id.
   *
   * @param edge_id target edge's id.
   * @returns true if `edge_id` is valid, otherwise false.
   */
  bool remove_edge(EdgeId edge_id)
  {
    auto edge_iter = entities_map_.find(edge_id);
    if (edge_iter == entities_map_.end() || !edge_iter->second.is_edge())
      return false;

    const auto edge_item = edge_iter->second.as_edge();

    matrix_.at(edge_item.n, edge_item.m) = std::nullopt;

    registry_.destroy(edge_id);
    entities_map_.erase(edge_iter);

    --edges_count_;

    return true;
  }

  /** count of edges of given node's `node_id` in given direction `dir`.
   *
   * direction `dir` is irrelevant when graph is undirected.
   *
   * @param node_id target node's id.
   * @returns an optional containing size_t count number if `node_id` is valid,
   *          otherwise std::nullopt.
   */
  auto get_degree(NodeId node_id, EdgeDir dir = EdgeDir::inout) const
    -> std::optional<std::size_t>
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return std::nullopt;

    std::size_t node_idx = node_iter->second.as_node().idx;

    // undirected graph (all dir values are same here)
    if constexpr (is_undirected) {
      std::size_t count = 0;

      for (std::size_t i = 0; i < node_idx; ++i)
        count += matrix_.at(node_idx, i).has_value();

      for (std::size_t i = node_idx+1; i < matrix_.size(); ++i)
        count += matrix_.at(i, node_idx).has_value();

      return count;
    }

    // directed graph
    std::size_t count = 0;

    bool is_in  = dir != EdgeDir::out;
    bool is_out = !is_in;

    for (std::size_t i = 0; i < matrix_.size(); ++i) {
      count += matrix_.at(node_idx, i).has_value() & is_out;
      count += matrix_.at(i, node_idx).has_value() & is_in;
    }

    count -= matrix_.at(node_idx, node_idx).has_value() & (is_in & is_out);

    return count;
  }

  /** returns view of edges of a given node's `node_id` in direction `dir`.
   *
   * to get 1st order neighbours of a node, combine this with get_edge_nodes.
   *
   * @param node_id target node's id.
   * @returns a range view to edges of target node, if `node_id` is valid,
   *          otherwise an empty range view.
   */
  auto get_edges_of(NodeId node_id, EdgeDir dir = EdgeDir::inout) const
  {
    auto matrix_size = matrix_.size();

    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      matrix_size = 0; // iota will be an empty range.

    auto node_idx = node_iter->second.as_node().idx;

    return ranges::views::iota(0)
      | ranges::views::take(matrix_size)
      | ranges::views::transform(
          [&matrix=matrix_, node_idx=node_idx, dir=dir](std::size_t idx)
          {
            if constexpr (is_undirected)
            {
              auto i = node_idx, j = idx;
              if (j == i)
                return std::optional<entity_type>{};

              if (j > i)
                std::swap(i, j);

              return matrix.at(i, j);
            }
            else // if directed
            {
              // if EdgeDir::out or EdgeDir::inout
              if (dir != EdgeDir::in) return matrix.at(node_idx, idx);

              // if EdgeDir::in or EdgeDir::inout
              if (dir != EdgeDir::out) return matrix.at(idx, node_idx);
            }
          }
        )
      | ranges::views::filter([](auto opt_edge_id) { return opt_edge_id.has_value(); })
      | ranges::views::transform([](auto opt_edge_id) { return opt_edge_id.value(); });
  }

  /** view of all nodes in graph.
   *
   * @returns a range view to all nodes in graph.
   */
  auto nodes_view() const
  {
    return entities_map_
      | ranges::views::filter(
          [](const auto& kvpair) { return kvpair.second.is_node(); }
        )
      | ranges::views::transform([](const auto& kvpair) { return kvpair.first; });
  }

  /** view of all edges in graph.
   *
   * @returns a range view to all edges in graph.
   */
  auto edges_view() const
  {
    return entities_map_
      | ranges::views::filter(
          [](const auto& kvpair) { return kvpair.second.is_edge(); }
        )
      | ranges::views::transform([](const auto& kvpair) { return kvpair.first; });
  }

  /** view of all clusters in graph.
   *
   * @returns a range view to all clusters in graph.
   */
  auto clusters_view() const
  {
    return entities_map_
      | ranges::views::filter(
          [](const auto& kvpair) { return kvpair.second.is_cluster(); }
        )
      | ranges::views::transform([](const auto& kvpair) { return kvpair.first; });
  }

  std::size_t node_count()    const noexcept { return nodes_count_;    }
  std::size_t edge_count()    const noexcept { return edges_count_;    }
  std::size_t cluster_count() const noexcept { return clusters_count_; }
};

}  // namespace gviz::graph

#endif  // GVIZARD_GRAPH_GRAPH_HPP_
