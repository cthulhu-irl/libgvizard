#ifndef GVIZARD_ATTRTYPES_POINT_HPP_
#define GVIZARD_ATTRTYPES_POINT_HPP_

#include <type_traits>
#include <utility>
#include <vector>

namespace gvizard::attrtypes {

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
struct PointType : public Point3D<T> {
  constexpr PointType(T x, T y, T z = {})
    : Point3D<T>(std::move(x), std::move(y), std::move(z))
  {}

  constexpr PointType(Point2D<T> p)
    : Point3D<T>(std::move(p.x), std::move(p.y), T{})
  {}

  constexpr PointType(Point3D<T> p)
    : Point3D<T>(std::move(p.x), std::move(p.y), std::move(p.z))
  {}
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_POINT_HPP_
