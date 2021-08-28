#ifndef GVIZARD_ATTRTYPES_COLOR_HPP_
#define GVIZARD_ATTRTYPES_COLOR_HPP_

#include <gvizard/colors.hpp>

namespace gvizard::attrtypes {

using ColorType = colors::Color;

template <typename ColorT = colors::RGB,
          template <typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
using ColorList = Vec<colors::WeightedColor<ColorT>>;

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
