#ifndef GVIZARD_ATTRTYPES_SPLINE_HPP_
#define GVIZARD_ATTRTYPES_SPLINE_HPP_

#include <tuple>
#include <optional>
#include <vector>

#include "gvizard/attrtypes/point.hpp"

namespace gvizard::attrtypes {

using spline_point_type = Point2D<double>;
using spline_triple_type =
  std::tuple<spline_point_type, spline_point_type, spline_point_type>;

// TODO use something other than std::vector since it doesn't support SBO
template <template<typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
struct Spline final {
  spline_point_type point;

  std::optional<spline_point_type> endp{};
  std::optional<spline_point_type> startp{};

  Vec<spline_triple_type, VecArgs...> triples{};

  constexpr Spline& set_point(const spline_point_type& newpoint)
  {
    point = newpoint;
    return *this;
  }

  constexpr Spline& set_endp(const spline_point_type& endpoint)
  {
    endp = endpoint;
    return *this;
  }

  constexpr Spline& set_startp(const spline_point_type& startpoint)
  {
    startp = startpoint;
    return *this;
  }

  constexpr Spline& add_triples(const spline_triple_type& triple)
  {
    triples.push_back(triple);
    return *this;
  }
};

// TODO use something other than std::vector since it doesn't support SBO
template <template<typename, typename ...> typename Vec = std::vector,
          typename SplineT = Spline<std::vector>,
          typename ...VecArgs>
struct SplineType final {
  using spline_type = SplineT;

  Vec<spline_type, VecArgs...> splines{};

  constexpr SplineType& add_spline(const spline_type& spline)
  {
    splines.push_back(spline);
    return *this;
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_SPLINE_HPP_
