#ifndef GVIZARD_ATTRTYPES_POINT_HPP_
#define GVIZARD_ATTRTYPES_POINT_HPP_

#include <type_traits>
#include <utility>

namespace gvizard::attrtypes {

template <typename T>
struct Point2D {
  T x;
  T y;

  Point2D() : x{}, y{} {}
  Point2D(T x, T y)
    : x(std::move(x))
    , y(std::move(y))
  {}

  template <typename U>
  Point2D& operator+(const Point2D<U>& other)
  {
    x += other.x;
    y += other.y;

    return *this;
  }

  template <typename U>
  Point2D& operator-(const Point2D<U>& other)
  {
    x -= other.x;
    y -= other.y;

    return *this;
  }
};

template <typename T>
struct Point3D {
  T x;
  T y;
  T z;

  Point3D() : x{}, y{}, z{} {}
  Point3D(T x, T y, T z)
    : x(std::move(x))
    , y(std::move(y))
    , z(std::move(z))
  {}

  template <typename U>
  Point3D& operator+(const Point3D<U>& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
  }

  template <typename U>
  Point3D& operator-(const Point3D<U>& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_POINT_HPP_
