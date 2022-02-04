#ifndef GVIZARD_ATTRTYPES_COLOR_HPP_
#define GVIZARD_ATTRTYPES_COLOR_HPP_

#include "gvizard/colors.hpp"

namespace gviz::attrtypes {

using ColorType = colors::Color;

template <typename ColorT = colors::RGB,
          template <typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
using ColorList = Vec<colors::WeightedColor<ColorT>>;

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
