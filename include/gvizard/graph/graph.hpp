#ifndef GVIZARD_GRAPH_GRAPH_HPP_
#define GVIZARD_GRAPH_GRAPH_HPP_

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <variant>

#include "gvizard/registry/attrset.hpp"
#include "gvizard/registry/attrset_registry.hpp"
#include "gvizard/views.hpp"
#include "gvizard/utils.hpp"

#include "gvizard/graph/dynamic_square_matrix.hpp"
#include "gvizard/graph/dynamic_half_square_matrix.hpp"

/** an adjancency-matrix implementation of graph with internal registry.
 */
namespace gviz::graph {

struct no_view_t {};

enum class EntityTypeEnum { node, edge, cluster, graph };

enum class GraphDir : int { undirected = 0, directed = 1 };
enum class EdgeDir  : int { in = 1, out = 2, inout = 3 };

template <typename Registry, GraphDir DirV = GraphDir::undirected>
class Graph {
  using entity_type = typename Registry::entity_type;

 public:
  using NodeId    = entity_type;
  using EdgeId    = entity_type;
  using ClusterId = entity_type;

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

  struct ClusterItem {};

  class Item final {
    EntityTypeEnum type_;
    union {
      NodeItem    node_;
      EdgeItem    edge_;
      ClusterItem cluster_;
    };

   public:
    Item() {} // undefined behavior

    constexpr Item(NodeItem node) noexcept
      : type_(EntityTypeEnum::node), node_(std::move(node))
    {}

    constexpr Item(EdgeItem edge) noexcept
      : type_(EntityTypeEnum::edge), edge_(std::move(edge))
    {}

    constexpr Item(ClusterItem cluster) noexcept
      : type_(EntityTypeEnum::edge), cluster_(std::move(cluster))
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

  // iterators declarations, defined after public methods in private section
  class ClusterNodesIterator;
  class NodeEdgesIterator;

 private:
  constexpr static bool is_undirected = DirV == GraphDir::undirected;

  using optional_entity_type = std::optional<entity_type>;

  using matrix_type =
    std::conditional_t<
      is_undirected,
      detail::DynamicSquareMatrix<optional_entity_type>,
      detail::DynamicHalfSquareMatrix<optional_entity_type>
    >;
  using map_type = std::unordered_map<entity_type, Item>;
  using registry_type = Registry;

  matrix_type   matrix_{};
  map_type      entities_map_{};
  registry_type registry_{};

  std::size_t nodes_count_    = 0;
  std::size_t edges_count_    = 0;
  std::size_t clusters_count_ = 0;

 public:
  auto create_cluster() -> ClusterId
  {
    auto cluster_id = registry_.create();

    entities_map_[cluster_id] = ClusterItem{};

    return cluster_id;
  }

  bool add_to_cluster(ClusterId cluster_id, NodeId node_id)
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return false;

    const auto cluster_iter = entities_map_.find(cluster_id);
    if (cluster_id == entities_map_.end() || !cluster_iter->second.is_cluster())
      return false;

    auto& node_item = node_iter->second.as_node();
    node_item.cluster_id = cluster_id;

    return true;
  }

  auto create_node() -> NodeId
  {
    auto node_id = registry_.create();
    const auto idx = matrix_.size();

    matrix_.add_rowcol(1, std::nullopt);
    entities_map_[node_id] = NodeItem{idx};

    return node_id;
  }

  auto create_node_in(ClusterId cluster_id) -> NodeId
  {
    auto node_id = registry_.create();
    const auto idx = matrix_.size();

    matrix_.add_rowcol(1, std::nullopt);
    entities_map_[node_id] = NodeItem{idx, cluster_id};

    return node_id;
  }

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
      // this must be ensured to be impossible in design, not runtime.
      //if (node_a_idx == node_b_idx)
      //  return std::nullopt;

      // mirroring triangle
      if (node_a_idx < node_b_idx) {
        std::swap(node_a_id, node_b_id);
        std::swap(node_a_idx, node_b_idx);
      }
    }

    auto edge_id = registry_.create();

    entities_map_[edge_id] = EdgeItem{
      node_a_idx,
      node_b_idx,
      node_a_id,
      node_b_id
    };

    *matrix_.at(node_a_idx, node_b_idx) = edge_id;

    return edge_id;
  }

  auto get_cluster_nodes(ClusterId cluster_id) const
    -> IteratorView<NodeId, ClusterNodesIterator>
  {
    // empty view for invalid cluster_id
    if (entities_map_.find(cluster_id) == entities_map_.end()) {
      auto empty_iter = ClusterNodesIterator(entities_map_.end());
      return { empty_iter, empty_iter };
    }

    auto iter = ClusterNodeIteratorCallback(
      entities_map_.begin(),
      entities_map_.end(),
      cluster_id
    );

    return { iter.begin(), iter.end() };
  }

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

    return *matrix_.at(node_a_idx, node_b_idx);
  }

  auto get_edge_nodes(EdgeId edge_id)
    -> std::optional<std::pair<NodeId, NodeId>>
  {
    auto edge_iter = entities_map_.find(edge_id);
    if (edge_iter == entities_map_.end() || !edge_iter->second.is_edge())
      return std::nullopt;

    const auto node_a_id = edge_iter->second.as_edge().node_a_id;
    const auto node_b_id = edge_iter->second.as_edge().node_b_id;

    // order (node_a_idx > node_a_idx) must be ensured by design.
    return { node_a_id, node_b_id };
  }

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

  bool remove_edge(NodeId node_a_id, NodeId node_b_id)
  {
    auto opt_edge_id = get_edge_id(node_a_id, node_b_id);
    if (!opt_edge_id)
      return false;

    auto edge_item = entities_map_[*opt_edge_id];

    *matrix_.at(edge_item.n, edge_item.m) = std::nullopt;

    registry_.destroy(*opt_edge_id);
    entities_map_.erase(*opt_edge_id);

    --edges_count_;

    return true;
  }

  bool remove_edge(EdgeId edge_id)
  {
    auto edge_iter = entities_map_.find(edge_id);
    if (edge_iter == entities_map_.end() || !edge_iter->second.is_edge())
      return false;

    const auto edge_item = edge_iter->second.as_edge();

    *matrix_.at(edge_item.n, edge_item.m) = std::nullopt;

    registry_.destroy(edge_id);
    entities_map_.erase(edge_iter);

    --edges_count_;

    return true;
  }

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
        count += matrix_.at(node_idx, i);

      for (std::size_t i = node_idx+1; i < matrix_.size(); ++i)
        count += matrix_.at(i, node_idx);

      return count;
    }

    // directed graph
    std::size_t count = 0;

    bool is_in    = dir != EdgeDir::out;
    bool is_out   = !is_in;

    for (std::size_t i = 0; i < matrix_.size(); ++i) {
      count += matrix_.at(node_idx, i).has_value() & is_out;
      count += matrix_.at(i, node_idx).has_value() & is_in;
    }

    count -= matrix_.at(node_idx, node_idx).has_value() & (is_in & is_out);

    return count;
  }

  // returns a view to iterator of EdgeId elements.
  // to get 1st order neighbours of a node, combine this with get_edge_nodes.
  auto get_edges(NodeId node_id, EdgeDir dir = EdgeDir::inout) const
  {
    auto node_iter = entities_map_.find(node_id);
    if (node_iter == entities_map_.end() || !node_iter->second.is_node())
      return NodeEdgesIterator{};

    return NodeEdgesIterator(matrix_, node_id, dir);
  }

  auto nodes_view() const
  {
    const auto lambda = [this](NodeId)
      {
        for (const auto& [item_id, item] : entities_map_)
          if (item.is_node())
            return item_id;

        return std::nullopt;
      };

    return CallbackView<NodeId, decltype(lambda)>(lambda, NodeId{});
  }

  auto edges_view() const
  {
    const auto lambda = [this](EdgeId)
      {
        for (const auto& [item_id, item] : entities_map_)
          if (item.is_edge())
            return item_id;

        return std::nullopt;
      };

    return CallbackView<EdgeId, decltype(lambda)>(lambda, EdgeId{});
  }

  auto clusters_view() const
  {
    const auto lambda = [this](ClusterId)
      {
        for (const auto& [item_id, item] : entities_map_)
          if (item.is_cluster())
            return item_id;

        return std::nullopt;
      };

    return CallbackView<ClusterId, decltype(lambda)>(lambda, ClusterId{});
  }

  std::size_t node_count()    const noexcept { return nodes_count_;    }
  std::size_t edge_count()    const noexcept { return edges_count_;    }
  std::size_t cluster_count() const noexcept { return clusters_count_; }

  template <typename Callable>
  auto traversal(Callable&& func) -> CallbackView<NodeId, Callable>;

  template <typename Callable>
  auto traversal(Callable&& func, NodeId node_id)
    -> CallbackView<NodeId, Callable>;

  template <typename Callable>
  void traversal(no_view_t, Callable&& func, NodeId node_id);

 private:

  class ClusterNodesIterator final {
    using const_iterator = typename map_type::const_iterator;

    const_iterator iter_;
    const_iterator end_;
    ClusterId      target_cluster_id_;

    std::optional<NodeId> current_;

   public:
    // empty iterator
    explicit ClusterNodesIterator(const_iterator end)
      : iter_(std::move(end))
      , end_(iter_)
      , target_cluster_id_{} // dummy, other == *this won't pass.
      , current_(std::nullopt)
    {}

    ClusterNodesIterator(const_iterator iter,
                         const_iterator end,
                         ClusterId cluster_id)
      : iter_(std::move(iter))
      , end_(std::move(end_))
      , target_cluster_id_(cluster_id)
    {
      current_ = next();
    }

    auto begin() { return *this; }
    auto end()
    {
      return ClusterNodesIterator(end_, end_, target_cluster_id_);
    }

    ClusterNodesIterator& operator++()
    {
      if (!current_.has_value())
        return *this;

      current_ = next();
      return *this;
    }

    ClusterNodesIterator operator++(int)
    {
      if (!current_.has_value())
        return *this;

      auto tmp = *this;
      operator++();
      return tmp;
    }

    NodeId operator*() const { return *current_; }

    bool operator==(const ClusterNodesIterator& other) const
    {
      return iter_ == other.iter_ 
          && target_cluster_id_ == other.target_cluster_id_
          || (!current_ && !other.current_);
    }

    bool operator!=(const ClusterNodesIterator& other) const
    {
      return !(*this == other);
    }

   private:
    auto next() -> std::optional<NodeId>
    {
      for (; iter_ != end_; ++iter_)
      {
        if (!iter_.second.is_node()) continue;

        auto opt_cluster_id = iter_.second.as_node().cluster_id;
        if (opt_cluster_id && *opt_cluster_id == target_cluster_id_)
          return iter_.first;
      }

      return std::nullopt;
    }
  };

  class NodeEdgesIterator final {
    utils::OptionalRef<const matrix_type> matrix_;
    std::size_t                           node_idx_;
    EdgeDir                               dir_;

    std::size_t i_ = 0; // for rows
    std::size_t j_ = 0; // for cols

    std::optional<EdgeId> current_;

   public:
    // empty or end iterator
    explicit NodeEdgesIterator(std::size_t node_idx = {})
      : matrix_(utils::nulloptref)
      , node_idx_(node_idx)
      , current_(std::nullopt)
    {}

    NodeEdgesIterator(const matrix_type& matrix,
                      std::size_t node_idx,
                      EdgeDir dir)
      : matrix_(std::addressof(matrix))
      , node_idx_(node_idx)
      , dir_(dir)
    {
      if constexpr (is_undirected) {
        current_ = next_undirected();
      } else {
        current_ = next_directed();
      }
    }

    auto begin() { return *this; }
    auto end()
    {
      return NodeEdgesIterator(node_idx_);
    }

    NodeEdgesIterator& operator++()
    {
      if (!current_.has_value())
        return *this;

      if constexpr (is_undirected)
        current_ = next_undirected();
      else
        current_ = next_directed();

      return *this;
    }

    NodeEdgesIterator operator++(int)
    {
      if (!current_.has_value())
        return *this;

      auto tmp = *this;
      operator++();
      return tmp;
    }

    auto operator->() const { return current_; }
    NodeId operator*() const { return *current_; }

    bool operator==(const NodeEdgesIterator& other) const
    {
      return current_ == other.current_ && node_idx_ == other.node_idx_;
    }

    bool operator!=(const ClusterNodesIterator& other) const
    {
      return current_ != other.current_ || node_idx_ != other.node_idx_;
    }

   private:
    auto next_directed() -> std::optional<EdgeId>
    {
      if (dir_ != EdgeDir::in) // dir_ is EdgeDir::out or EdgeDir::inout
      {
        for (; i_ < matrix_->size(); ++i_) {
          const auto opt_edge_id = matrix_.at(node_idx_, i_);
          if (opt_edge_id)
            return *opt_edge_id;
        }
      }

      if (dir_ != EdgeDir::out) // dir_ is EdgeDir::in or EdgeDir::inout
      {
        for (; j_ < matrix_->size(); ++j_) {
          const auto opt_edge_id = matrix_.at(j_, node_idx_);
          if (opt_edge_id && j_ != node_idx_)
            return *opt_edge_id;
        }
      }

      return std::nullopt;
    }

    auto next_undirected() -> std::optional<EdgeId>
    {
      // in/out/inout edge directions are all same here...

      for (; i_ < node_idx_; ++i_) {
        const auto opt_edge_id = matrix_.at(node_idx_, i_);
        if (opt_edge_id)
          return *opt_edge_id;
      }

      if (i_ == node_idx_) ++i_;

      for (; i_ < matrix_->size(); ++i_) {
        const auto opt_edge_id = matrix_.at(i_, node_idx_);
        if (opt_edge_id)
          return *opt_edge_id;
      }

      return std::nullopt;
    }
  };
};

}  // namespace gviz::graph

#endif  // GVIZARD_GRAPH_GRAPH_HPP_
