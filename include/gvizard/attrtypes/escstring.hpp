#ifndef GVIZARD_ATTRTYPES_ESCSTRING_HPP_
#define GVIZARD_ATTRTYPES_ESCSTRING_HPP_

#include <string>
#include <string_view>

namespace gvizard::attrtypes {

template <typename StringT = std::string>
class EscString final {
  using iterator = typename StringT::iterator;
  using const_iterator = typename StringT::const_iterator;

  struct Occurences final {
    std::size_t graph = 0;
    std::size_t node = 0;
    std::size_t edge = 0;
    std::size_t label = 0;
    std::size_t head = 0;
    std::size_t tail = 0;

    /* requires too much memory to overflow */
    constexpr std::size_t sum() const noexcept
    {
      return graph + node + edge + label + head + tail;
    }
  };
 
  Occurences occurences{};
  StringT format_{};

 public:
  constexpr EscString(const char *format, std::size_t size)
    : format_(format, size)
  {
    occurences =
      count_occurences(std::cbegin(format_), std::cend(format_));
  }

  constexpr EscString(StringT format) : format_(std::move(format))
  {
    occurences
      = count_occurences(std::cbegin(format_), std::cend(format_));
  }

  constexpr Occurences
  get_occurences() const noexcept { return occurences; }

  constexpr std::size_t apply_size(
      const std::string_view& graph_name="",
      const std::string_view& node_name="",
      const std::string_view& edge_name="",
      const std::string_view& label_name="",
      const std::string_view& head_name="",
      const std::string_view& tail_name="") const
  {
    return format_.size() - occurences.sum() * 2
           + graph_name.size() * occurences.graph
           + node_name.size()  * occurences.node
           + edge_name.size()  * occurences.edge
           + label_name.size() * occurences.label;
  }

  template <typename OutStringT = std::string>
  constexpr OutStringT apply(
      const std::string_view& graph_name="",
      const std::string_view& node_name="",
      const std::string_view& edge_name="",
      const std::string_view& label_name="",
      const std::string_view& head_name="",
      const std::string_view& tail_name="") const
  {
    OutStringT output{};

    const auto outsize = apply_size(graph_name, node_name, edge_name,
                                    label_name, head_name, tail_name);

    output.reserve(outsize);

    auto str = std::cbegin(format_);
    auto end = std::cend(format_);

    for (; str != end; ++str)
    {
      if (*str != '\\') {
        output += *str;
        continue;
      }

      switch (*++str)
      {
        case 'G':  output += graph_name; break;
        case 'N':  output += node_name;  break;
        case 'E':  output += edge_name;  break;
        case 'L':  output += label_name; break;
        case 'H':  output += head_name;  break;
        case 'T':  output += tail_name;  break;
        case '\\': output += '\\';       break;
        default:
          output += '\\';
          output += *str;
      }
    }

    return output;
  }

 private:
  constexpr static Occurences
  count_occurences(const_iterator str, const_iterator end) noexcept
  {
    Occurences ret;

    for (; str != end; ++str)
    {
      if (*str != '\\') continue;

      switch (*++str)
      {
        case 'G': ++ret.graph; break;
        case 'N': ++ret.node;  break;
        case 'E': ++ret.edge;  break;
        case 'L': ++ret.label; break;
        case 'H': ++ret.head;  break;
        case 'T': ++ret.tail;  break;
      }
    }

    return ret;
  }
};

constexpr auto operator "" _escstr(const char *str, std::size_t size)
{
  return EscString<std::string_view>(str, size);
}

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ESCSTRING_HPP_
