#ifndef GVIZARD_ATTRTYPES_LABEL_HPP_
#define GVIZARD_ATTRTYPES_LABEL_HPP_

#include <string>

#include "gvizard/attrtypes/escstring.hpp"

namespace gvizard::attrtypes {

template <typename Str = std::string>
using Label = EscString<Str>;

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_LABEL_HPP_
