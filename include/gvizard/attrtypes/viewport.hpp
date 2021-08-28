#ifndef GVIZARD_ATTRTYPES_VIEWPORT_HPP_
#define GVIZARD_ATTRTYPES_VIEWPORT_HPP_

#include <string>
#include <variant>

#include <gvizard/attrtypes/point.hpp>

namespace gvizard::attrtypes {

struct ViewPortXY final {
  Point2D<double> size = {0., 0.};
  double zoom = 1.;
  Point2D<double> center{};

  constexpr bool operator==(const ViewPortXY& other) const noexcept
  {
    return size == other.size
        && zoom == other.zoom
        && center == other.center;
  }

  constexpr bool operator!=(const ViewPortXY& other) const noexcept
  {
    return size == other.size
        && zoom == other.zoom
        && center == other.center;
  }
};

struct ViewPortS final {
  Point2D<double> size = {0., 0.};
  double zoom = 1.;
  std::string center{};

  constexpr bool operator==(const ViewPortS& other) const noexcept
  {
    return size == other.size
        && zoom == other.zoom
        && center == other.center;
  }

  constexpr bool operator!=(const ViewPortS& other) const noexcept
  {
    return size == other.size
        && zoom == other.zoom
        && center == other.center;
  }
};

using ViewPortType = std::variant<ViewPortXY, ViewPortS>;

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_VIEWPORT_HPP_
