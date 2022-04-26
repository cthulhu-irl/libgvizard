#ifndef GVIZARD_ATTRTYPES_STYLE_HPP_
#define GVIZARD_ATTRTYPES_STYLE_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>

#include "gvizard/utils.hpp"

namespace gviz::attrtypes {

enum class CommonStyle : uint8_t {
  none = 0,
  dashed,
  dotted,
  solid,
  invis,
  bold
};

enum class NodeStyleOnly : uint8_t {
  none = 0,
  filled,
  striped,
  wedged,
  diagonals,
  rounded,
  radial
};

enum class EdgeStyleOnly : uint8_t {
  none = 0,
  tapered
};

enum class ClusterStyleOnly : uint8_t {
  none = 0,
  filled,
  striped,
  rounded,
  radial
};

struct StyleItem final {
  std::string name;
  std::vector<std::string> args;

  bool operator==(const StyleItem& other) const
  {
    return name == other.name && args == other.args;
  }

  bool operator!=(const StyleItem& other) const
  {
    return name != other.name || args != other.args;
  }
};

struct BuiltinStyleItem final {
  using builtin_style_type = std::variant<CommonStyle, NodeStyleOnly,
                                        EdgeStyleOnly, ClusterStyleOnly>;
  builtin_style_type name;
  std::vector<std::string> args;

  BuiltinStyleItem(builtin_style_type style,
                    std::vector<std::string> vecargs = {})
    : name(style)
    , args(std::move(vecargs))
  {}

  bool operator==(const BuiltinStyleItem& other) const
  {
    return name == other.name && args == other.args;
  }

  bool operator!=(const BuiltinStyleItem& other) const
  {
    return name != other.name || args != other.args;
  }

  StyleItem to_style_item() const
  {
    return StyleItem{
      std::visit(
        [](auto style) -> std::string
        {
          using enum_type = decltype(style);
          return bool(style)
            ? std::string(utils::EnumHelper<enum_type>::to_str(style))
            : std::string("");
        },
        name
      ),
      args
    };
  }
};

struct Style final {
  using item_type = std::variant<BuiltinStyleItem, StyleItem>;

  constexpr static auto to_style_item =
    [](const item_type& item)
    {
      return std::visit(
        utils::LambdaVisitor{
          [](const StyleItem& arg)        { return arg;                 },
          [](const BuiltinStyleItem& arg) { return arg.to_style_item(); }
        },
        item
      );
    };

  std::vector<item_type> items{};

  Style() : items{} {}

  Style(CommonStyle style)      : Style(BuiltinStyleItem(style)) {}
  Style(NodeStyleOnly style)    : Style(BuiltinStyleItem(style)) {}
  Style(EdgeStyleOnly style)    : Style(BuiltinStyleItem(style)) {}
  Style(ClusterStyleOnly style) : Style(BuiltinStyleItem(style)) {}

  Style(StyleItem styleitem)        { items.push_back(styleitem); }
  Style(BuiltinStyleItem styleitem) { items.push_back(styleitem); }

  Style(std::vector<item_type> vector) : items(std::move(vector)) {}

  bool operator==(const Style& other) const
  {
    return items == other.items;
  }

  bool operator!=(const Style& other) const
  {
    return items != other.items;
  }

  Style& all_style_items()
  {
    std::transform(
        std::begin(items), std::end(items),
        std::begin(items), to_style_item
    );
    return *this;
  }

  std::vector<StyleItem> to_style_item_vector() const
  {
    std::vector<StyleItem> style_items{};
    style_items.reserve(items.size());

    std::transform(
        std::begin(items), std::end(items),
        std::begin(style_items), to_style_item
    );
    return style_items;
  }
};

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_STYLE_HPP_
