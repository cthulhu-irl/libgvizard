#ifndef GVIZARD_ATTRTYPES_COLOR_HPP_
#define GVIZARD_ATTRTYPES_COLOR_HPP_

#include "gvizard/colors.hpp"

namespace gvizard::attrtypes {

using ColorType = colors::Color;

template <template <typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
using ColorList = Vec<WeightedColor>;

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_COLOR_HPP_
