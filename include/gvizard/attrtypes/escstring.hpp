#ifndef GVIZARD_ATTRTYPES_ESCSTRING_HPP_
#define GVIZARD_ATTRTYPES_ESCSTRING_HPP_

#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace gviz::attrtypes {

struct EscNameSetRef final {
  std::string_view graph{};
  std::string_view node{};
  std::string_view edge{};
  std::string_view label{};
  std::string_view head{};
  std::string_view tail{};

  template <typename StrT>
  constexpr EscNameSetRef& set_graph_str(const StrT& str)
  {
    graph = str;
    return *this;
  }

  template <typename StrT>
  constexpr EscNameSetRef& set_node_str(const StrT& str)
  {
    node = str;
    return *this;
  }

  template <typename StrT>
  constexpr EscNameSetRef& set_edge_str(const StrT& str)
  {
    edge = str;
    return *this;
  }

  template <typename StrT>
  constexpr EscNameSetRef& set_label_str(const StrT& str)
  {
    label = str;
    return *this;
  }

  template <typename StrT>
  constexpr EscNameSetRef& set_head_str(const StrT& str)
  {
    head = str;
    return *this;
  }

  template <typename StrT>
  constexpr EscNameSetRef& set_tail_str(const StrT& str)
  {
    tail = str;
    return *this;
  }
};

struct EscOccurences final {
  std::size_t graph = 0;
  std::size_t node  = 0;
  std::size_t edge  = 0;
  std::size_t label = 0;
  std::size_t head  = 0;
  std::size_t tail  = 0;

  /* requires too much memory to overflow */
  constexpr std::size_t sum() const noexcept
  {
    return graph + node + edge + label + head + tail;
  }

  constexpr bool operator==(const EscOccurences& other) const
  {
    return graph == other.graph && node  == other.node
        && edge  == other.edge  && label == other.label
        && head  == other.head  && tail  == other.tail;
  }

  constexpr bool operator!=(const EscOccurences& other) const
  {
    return graph != other.graph || node  != other.node
        || edge  != other.edge  || label != other.label
        || head  != other.head  || tail  != other.tail;
  }
};

template <typename StringT = std::string>
class EscString final {
  using iterator = typename StringT::iterator;
  using const_iterator = typename StringT::const_iterator;
 
  StringT       format_{};
  EscOccurences occurences_{};

 public:
  constexpr EscString() : format_{}, occurences_{} {}

  template <typename U,
            std::enable_if_t<!std::is_same_v<U, EscString>
                             && std::is_constructible_v<StringT, U>, bool> = true>
  constexpr EscString(U&& format)
    noexcept(std::is_nothrow_constructible_v<StringT, decltype(std::forward<U>(format))>)
    : format_(std::forward<U>(format))
  {
    occurences_ = count_occurences(format_);
  }

  template <typename U>
  constexpr EscString(const EscString<U>& other)
    noexcept(std::is_nothrow_constructible_v<StringT, const U&>)
    : format_(other.get_format_ref())
    , occurences_(other.get_occurences())
  {}

  template <typename U, std::enable_if_t<!std::is_same_v<U, EscString>, bool> = true>
  constexpr EscString& operator=(U format)
    noexcept(std::is_nothrow_constructible_v<StringT, decltype(std::forward<U>(format))>)
  {
    format_ = std::forward<U>(format);
    occurences_ = count_occurences(format_);
    return *this;
  }

  constexpr StringT        get_format()     const noexcept { return format_; }
  constexpr const StringT& get_format_ref() const noexcept { return format_; }

  template <typename U>
  constexpr void set_format(U&& format)
    noexcept(std::is_nothrow_assignable_v<StringT, decltype(std::forward<U>(format))>)
  {
    format_ = std::forward<U>(format);
    occurences_ = count_occurences(format_);
  }

  constexpr EscOccurences get_occurences() const noexcept
  {
    return occurences_;
  }

  constexpr bool operator==(const EscString& other) const
  {
    return occurences_ == other.occurences && format_ == other.format_;
  }

  constexpr bool operator!=(const EscString& other) const
  {
    return occurences_ != other.occurences || format_ != other.format_;
  }

  constexpr std::size_t apply_size(const EscNameSetRef& nameset) const
  {
    return format_.size() - 2 * occurences_.sum()
           + nameset.graph.size() * occurences_.graph
           + nameset.node.size()  * occurences_.node
           + nameset.edge.size()  * occurences_.edge
           + nameset.label.size() * occurences_.label
           + nameset.head.size()  * occurences_.head
           + nameset.tail.size()  * occurences_.tail;
  }

  std::string apply(const EscNameSetRef& nameset = {}) const
  {
    const auto outsize = apply_size(nameset);

    std::string output{};
    output.reserve(outsize);

    char last = '\0';
    for (const char cur : format_)
    {
      if (last == '\\') {
        switch (cur)
        {
          case 'G':  output += nameset.graph;     break;
          case 'N':  output += nameset.node;      break;
          case 'E':  output += nameset.edge;      break;
          case 'L':  output += nameset.label;     break;
          case 'H':  output += nameset.head;      break;
          case 'T':  output += nameset.tail;      break;
          case '\\': output += '\\';              break;
          default:
            output += '\\';
            output += cur;
        }
      }

      last = cur;
    }

    return output;
  }

 private:
  constexpr static EscOccurences count_occurences(const StringT& format) noexcept
  {
    EscOccurences ret{};

    char last = '\0';
    for (const char cur : format)
    {
      if (last == '\\') {
        switch (cur)
        {
          case 'G': ++ret.graph; break;
          case 'N': ++ret.node;  break;
          case 'E': ++ret.edge;  break;
          case 'L': ++ret.label; break;
          case 'H': ++ret.head;  break;
          case 'T': ++ret.tail;  break;
        }
      }

      last = cur;
    }

    return ret;
  }
};

}  // namespace gviz::attrtypes

constexpr auto operator "" _escsv(const char *str, std::size_t size)
{
  return gviz::attrtypes::EscString<std::string_view>(
      std::string_view(str, size)
  );
}

#endif  // GVIZARD_ATTRTYPES_ESCSTRING_HPP_
