#ifndef GVIZARD_ATTRTYPES_ESCSTRING_HPP_
#define GVIZARD_ATTRTYPES_ESCSTRING_HPP_

#include <string>
#include <string_view>

namespace gvizard::attrtypes {

struct EscNameSetRef final {
  const std::string_view& graph="";
  const std::string_view& node="";
  const std::string_view& edge="";
  const std::string_view& label="";
  const std::string_view& head="";
  const std::string_view& tail="";
};

template <typename StringT = std::string>
class EscString final {
  using iterator = typename StringT::iterator;
  using const_iterator = typename StringT::const_iterator;

  constexpr static auto backslash_char_sv = std::string_view("\\", 1);

  template <typename StrT = std::string>
  constexpr static std::decay_t<StrT(std::size_t)> default_outstring_init =
    +[](std::size_t size) -> StrT
    {
      auto ret = StrT{};
      ret.reserve(size);
      return ret;
    };

  template <typename StrT = std::string>
  constexpr static std::decay_t<void(StrT&, const std::string_view&)>
  default_outstring_append =
    +[](StrT& lhs, const std::string_view& rhs)
    {
      lhs += rhs;
    };

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

  constexpr StringT        get_format()     const { return format_; }
  constexpr const StringT& get_format_ref() const { return format_; }

  constexpr Occurences
  get_occurences() const noexcept { return occurences; }

  constexpr std::size_t apply_size(const EscNameSetRef& nameset) const
  {
    return format_.size() - occurences.sum() * 2
           + nameset.graph.size() * occurences.graph
           + nameset.node.size()  * occurences.node
           + nameset.edge.size()  * occurences.edge
           + nameset.label.size() * occurences.label
           + nameset.head.size()  * occurences.head
           + nameset.tail.size()  * occurences.tail;
  }

  template <typename Iterator>
  constexpr std::size_t apply(
      const EscNameSetRef& nameset,
      Iterator dstbegin, Iterator dstend) const
  {
    std::size_t idx = 0;
    auto iterator_appender =
      [&dstbegin, &dstend, &idx](const std::string_view& rhs) mutable
      {
        auto src = std::begin(rhs);
        auto dst = dstbegin + idx;
        auto end = dstend - 1; // NUL-termination
        for (; src != std::cend(rhs) && dst != end; ++src, ++dst, ++idx)
          *dst = *src;
      };

    apply<char>(
      nameset,
      [](std::size_t) -> char { return 0; }, // dummy/unused...
      [&iterator_appender](auto, auto str)
        mutable { iterator_appender(str); }
    );

    return idx;
  }

  template <typename OutStringT = std::string,
            typename Fappend = decltype(default_outstring_append<OutStringT>)>
  constexpr OutStringT apply_into(
      const EscNameSetRef& nameset,
      OutStringT output,
      Fappend append = default_outstring_append<OutStringT>) const
  {
    return apply<OutStringT>(
        nameset,
        [&]() -> OutStringT { return output; },
        append
    );
  }

  template <typename OutStringT = std::string,
            typename Finit = decltype(default_outstring_init<OutStringT>),
            typename Fappend = decltype(default_outstring_append<OutStringT>)>
  constexpr OutStringT apply(
      const EscNameSetRef& nameset,
      Finit init = default_outstring_init<OutStringT>,
      Fappend append = default_outstring_append<OutStringT>) const
  {
    const auto outsize = apply_size(nameset);

    auto output = init(outsize);

    auto str = std::cbegin(format_);
    auto end = std::cend(format_);

    for (; str != end; ++str)
    {
      if (*str != '\\') {
        append(output, std::string_view(str, 1));
        continue;
      }

      switch (*++str)
      {
        case 'G':  append(output, nameset.graph);     break;
        case 'N':  append(output, nameset.node);      break;
        case 'E':  append(output, nameset.edge);      break;
        case 'L':  append(output, nameset.label);     break;
        case 'H':  append(output, nameset.head);      break;
        case 'T':  append(output, nameset.tail);      break;
        case '\\': append(output, backslash_char_sv); break;
        default:
          append(output, backslash_char_sv);
          append(output, std::string_view(str, 1));
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
