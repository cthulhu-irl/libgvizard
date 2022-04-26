#ifndef GVIZARD_ATTRTYPES_POINT_HPP_
#define GVIZARD_ATTRTYPES_POINT_HPP_

#include <type_traits>
#include <utility>
#include <vector>
#include <variant>

#include "gvizard/utils.hpp"

namespace gviz::attrtypes {

template <typename T>
struct Point2D {
  using list_type = std::vector<Point2D<T>>;

  T x;
  T y;

  constexpr Point2D() : x{}, y{} {}
  constexpr Point2D(T x, T y)
    : x(std::move(x))
    , y(std::move(y))
  {}

  template <typename U>
  friend constexpr bool
  operator==(const Point2D& lhs, const Point2D<U>& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  template <typename U>
  friend constexpr bool
  operator!=(const Point2D& lhs, const Point2D<U>& rhs)
  {
    return lhs.x != rhs.x || lhs.y != rhs.y;
  }

  template <typename U>
  friend constexpr Point2D
  operator+(const Point2D& lhs, const Point2D<U>& rhs)
  {
    return Point2D{ lhs.x + rhs.x, lhs.y + rhs.y };
  }

  template <typename U>
  friend constexpr Point2D
  operator-(const Point2D& lhs, const Point2D<U>& rhs)
  {
    return Point2D{ lhs.x - rhs.x, lhs.y - rhs.y };
  }
};

template <typename T>
struct Point3D {
  using list_type = std::vector<Point3D<T>>;

  T x;
  T y;
  T z;

  constexpr Point3D() : x{}, y{}, z{} {}
  constexpr Point3D(T x, T y, T z)
    : x(std::move(x))
    , y(std::move(y))
    , z(std::move(z))
  {}

  template <typename U>
  friend constexpr bool
  operator==(const Point3D& lhs, const Point3D<U>& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }

  template <typename U>
  friend constexpr bool
  operator!=(const Point3D& lhs, const Point3D<U>& rhs)
  {
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
  }

  template <typename U>
  friend constexpr Point3D
  operator+(const Point3D& lhs, const Point3D<U>& rhs)
  {
    return Point3D{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
  }

  template <typename U>
  friend constexpr Point3D
  operator-(const Point3D& lhs, const Point3D<U>& rhs)
  {
    return Point3D{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
  }
};

template <typename T>
struct PointType final {
  using point_type = std::variant<Point2D<T>, Point3D<T>>;

  point_type point;

  constexpr PointType() : point(Point2D<T>(T(), T())) {}
  constexpr PointType(T x, T y)
    : point(Point2D<T>(std::move(x), std::move(y)))
  {}

  constexpr PointType(T x, T y, T z)
    : point(Point3D<T>(std::move(x), std::move(y), std::move(z)))
  {}

  constexpr PointType(point_type p) : point(std::move(p)) {}

  constexpr bool operator==(const PointType& other) const
  {
    return utils::LambdaVisit(
        point,
        [&](const Point2D<T>& p) { return p == Point2D<T>(other); },
        [&](const Point3D<T>& p) { return p == Point3D<T>(other); }
    );
  }

  constexpr bool operator!=(const PointType& other) const
  {
    return utils::LambdaVisit(
        point,
        [&](const Point2D<T>& p) { return p != Point2D<T>(other); },
        [&](const Point3D<T>& p) { return p != Point3D<T>(other); }
    );
  }

  constexpr bool operator+(const PointType& other) const
  {
    return utils::LambdaVisit(
        point,
        [&](const Point2D<T>& p) { return p + Point2D<T>(other); },
        [&](const Point3D<T>& p) { return p + Point3D<T>(other); }
    );
  }

  constexpr bool operator-(const PointType& other) const
  {
    return utils::LambdaVisit(
        point,
        [&](const Point2D<T>& p) { return p - Point2D<T>(other); },
        [&](const Point3D<T>& p) { return p - Point3D<T>(other); }
    );
  }

  constexpr operator Point2D<T>() const
  {
    return utils::LambdaVisit(
        point,
        [](const Point2D<T>& p) { return p; },
        [](const Point3D<T>& p) { return Point2D<T>{ p.x, p.y }; }
    );
  }

  constexpr operator Point3D<T>() const
  {
    return utils::LambdaVisit(
        point,
        [](const Point2D<T>& p) { return Point3D<T>{ p.x, p.y, T{} }; },
        [](const Point3D<T>& p) { return p; }
    );
  }
};

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_POINT_HPP_
