#ifndef GVIZARD_ATTRTYPES_ARROWTYPE_HPP_
#define GVIZARD_ATTRTYPES_ARROWTYPE_HPP_

#include <cstdint>
#include <tuple>
#include <array>

namespace gvizard::attrtypes {

enum class ArrowPrimaryShape : uint8_t {
  none = 0,
  box,
  crow,
  curve,
  icurve,
  diamond,
  dot,
  inv,
  normal,
  tee,
  vee
};

enum class ArrowOpen : bool {
  none = false,
  open = true
};

enum class ArrowSide : uint8_t {
  none = 0,
  left,
  right
};

struct ArrowModifier {
  ArrowSide side = ArrowSide::none;
  ArrowOpen open = ArrowOpen::none;
};

struct ArrowShape final {
  ArrowPrimaryShape shape = ArrowPrimaryShape::none;
  ArrowModifier modifier = {};

  constexpr ArrowShape& normalize() noexcept
  {
    modifier = normalized_modifier();
    return *this;
  }

  constexpr ArrowShape normalized() const noexcept
  {
    return { shape, normalized_modifier() };
  }

 private:
  constexpr ArrowModifier normalized_modifier() const noexcept
  {
    switch (shape)
    {
      case ArrowPrimaryShape::box:
      case ArrowPrimaryShape::diamond:
      case ArrowPrimaryShape::inv:
      case ArrowPrimaryShape::normal:
        return modifier;

      case ArrowPrimaryShape::crow:
      case ArrowPrimaryShape::curve:
      case ArrowPrimaryShape::icurve:
      case ArrowPrimaryShape::tee:
      case ArrowPrimaryShape::vee:
        return { modifier.side };

      case ArrowPrimaryShape::dot:
        return { ArrowSide::none, modifier.open };

      default: return {};
    }
  }
};

struct ArrowType {
  alignas(4) ArrowShape shape1{};
  alignas(4) ArrowShape shape2{};
  alignas(4) ArrowShape shape3{};
  alignas(4) ArrowShape shape4{};

  constexpr ArrowType& normalize() noexcept
  {
    shape1.normalize();
    shape2.normalize();
    shape3.normalize();
    shape4.normalize();
    return *this;
  }

  constexpr ArrowType normalized() const noexcept
  {
    return {
      shape1.normalized(),
      shape2.normalized(),
      shape3.normalized(),
      shape4.normalized()
    };
  }

  constexpr std::tuple<ArrowShape, ArrowShape, ArrowShape, ArrowShape>
  as_tuple() const noexcept
  {
    return { shape1, shape2, shape3, shape4 };
  }

  constexpr std::array<ArrowShape, 4>
  as_array() const noexcept
  {
    return { shape1, shape2, shape3, shape4 };
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_ARROWTYPE_HPP_
