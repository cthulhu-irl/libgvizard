#ifndef GVIZARD_ATTRTYPES_LABEL_HPP_
#define GVIZARD_ATTRTYPES_LABEL_HPP_

#include <string>

#include "gvizard/attrtypes/escstring.hpp"

namespace gviz::attrtypes {

template <typename Str = std::string>
using Label = EscString<Str>;

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_LABEL_HPP_
