#ifndef GVIZARD_ATTRTYPES_ARROWTYPE_HPP_
#define GVIZARD_ATTRTYPES_ARROWTYPE_HPP_

#include <cstdint>
#include <tuple>
#include <array>

namespace gviz::attrtypes {

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

  constexpr ArrowModifier(ArrowSide arg_side = ArrowSide::none,
                          ArrowOpen arg_open = ArrowOpen::none)
    : side(arg_side)
    , open(arg_open)
  {}

  constexpr bool operator==(const ArrowModifier& other) const noexcept
  {
    return side == other.side && open == other.open;
  }

  constexpr bool operator!=(const ArrowModifier& other) const noexcept
  {
    return side != other.side || open != other.open;
  }
};

struct ArrowShape final {
  ArrowPrimaryShape shape    = ArrowPrimaryShape::none;
  ArrowModifier     modifier = {};

  constexpr ArrowShape(ArrowPrimaryShape arg_shape = ArrowPrimaryShape::none,
                       ArrowModifier     arg_modifier = {})
    : shape(arg_shape)
    , modifier(arg_modifier)
  {}

  constexpr bool operator==(const ArrowShape& other) const noexcept
  {
    return shape == other.shape && modifier == other.modifier;
  }

  constexpr bool operator!=(const ArrowShape& other) const noexcept
  {
    return shape != other.shape || modifier != other.modifier;
  }

  constexpr bool operator==(const ArrowPrimaryShape& other) const noexcept
  {
    return shape == other && modifier == ArrowModifier{};
  }

  constexpr bool operator!=(const ArrowPrimaryShape& other) const noexcept
  {
    return shape != other || modifier != ArrowModifier{};
  }

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

  constexpr ArrowType(ArrowShape s1 = {}, ArrowShape s2 = {},
                      ArrowShape s3 = {}, ArrowShape s4 = {})
    : shape1(s1)
    , shape2(s2)
    , shape3(s3)
    , shape4(s4)
  {}

  constexpr bool operator==(const ArrowType& other) const noexcept
  {
    return shape1 == other.shape1
        && shape2 == other.shape2
        && shape3 == other.shape3
        && shape4 == other.shape4;
  }

  constexpr bool operator!=(const ArrowType& other) const noexcept
  {
    return shape1 != other.shape1
        || shape2 != other.shape2
        || shape3 != other.shape3
        || shape4 != other.shape4;
  }

  constexpr bool operator==(const ArrowShape& other) const noexcept
  {
    return shape1 == other
        && shape2 == ArrowPrimaryShape::none
        && shape3 == ArrowPrimaryShape::none
        && shape4 == ArrowPrimaryShape::none;
  }

  constexpr bool operator!=(const ArrowShape& other) const noexcept
  {
    return shape1 != other
        || shape2 != ArrowPrimaryShape::none
        || shape3 != ArrowPrimaryShape::none
        || shape4 != ArrowPrimaryShape::none;
  }

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

struct arrowshapes {

  // static struct
  arrowshapes() = delete;

  // -- none
  constexpr static inline const ArrowShape none = {
    ArrowPrimaryShape::none
  };

  // -- normal
  constexpr static inline const ArrowShape normal = {
    ArrowPrimaryShape::normal
  };

  constexpr static inline const ArrowShape lnormal = {
    ArrowPrimaryShape::normal, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rnormal = {
    ArrowPrimaryShape::normal, { ArrowSide::right }
  };

  constexpr static inline const ArrowShape onormal = {
    ArrowPrimaryShape::normal, { ArrowSide::none, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape olnormal = {
    ArrowPrimaryShape::normal, { ArrowSide::none, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape ornormal = {
    ArrowPrimaryShape::normal, { ArrowSide::none, ArrowOpen::open }
  };

  // -- box
  constexpr static inline const ArrowShape box = {
    ArrowPrimaryShape::box
  };

  constexpr static inline const ArrowShape lbox = {
    ArrowPrimaryShape::box, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rbox = {
    ArrowPrimaryShape::box, { ArrowSide::right }
  };

  constexpr static inline const ArrowShape obox = {
    ArrowPrimaryShape::box, { ArrowSide::none, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape olbox = {
    ArrowPrimaryShape::box, { ArrowSide::left, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape orbox = {
    ArrowPrimaryShape::box, { ArrowSide::right, ArrowOpen::open }
  };

  // -- crow
  constexpr static inline const ArrowShape crow = {
    ArrowPrimaryShape::crow
  };

  constexpr static inline const ArrowShape lcrow = {
    ArrowPrimaryShape::crow, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rcrow = {
    ArrowPrimaryShape::crow, { ArrowSide::right }
  };

  // -- diamond
  constexpr static inline const ArrowShape diamond = {
    ArrowPrimaryShape::diamond
  };

  constexpr static inline const ArrowShape ldiamond = {
    ArrowPrimaryShape::diamond, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rdiamond = {
    ArrowPrimaryShape::diamond, { ArrowSide::right }
  };

  constexpr static inline const ArrowShape odiamond = {
    ArrowPrimaryShape::diamond, { ArrowSide::none, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape oldiamond = {
    ArrowPrimaryShape::diamond, { ArrowSide::left, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape ordiamond = {
    ArrowPrimaryShape::diamond, { ArrowSide::right, ArrowOpen::open }
  };

  // -- dot
  constexpr static inline const ArrowShape dot = {
    ArrowPrimaryShape::dot
  };

  constexpr static inline const ArrowShape odot = {
    ArrowPrimaryShape::dot, { ArrowSide::none, ArrowOpen::open }
  };

  // -- inv
  constexpr static inline const ArrowShape inv = {
    ArrowPrimaryShape::inv
  };

  constexpr static inline const ArrowShape linv = {
    ArrowPrimaryShape::inv, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rinv = {
    ArrowPrimaryShape::inv, { ArrowSide::right }
  };

  constexpr static inline const ArrowShape oinv = {
    ArrowPrimaryShape::inv, { ArrowSide::none, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape olinv = {
    ArrowPrimaryShape::inv, { ArrowSide::left, ArrowOpen::open }
  };

  constexpr static inline const ArrowShape orinv = {
    ArrowPrimaryShape::inv, { ArrowSide::right, ArrowOpen::open }
  };

  // -- tee
  constexpr static inline const ArrowShape tee = {
    ArrowPrimaryShape::tee
  };

  constexpr static inline const ArrowShape ltee = {
    ArrowPrimaryShape::tee, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rtee = {
    ArrowPrimaryShape::tee, { ArrowSide::right }
  };

  // -- vee
  constexpr static inline const ArrowShape vee = {
    ArrowPrimaryShape::vee
  };

  constexpr static inline const ArrowShape lvee = {
    ArrowPrimaryShape::vee, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rvee = {
    ArrowPrimaryShape::vee, { ArrowSide::right }
  };

  // -- curve
  constexpr static inline const ArrowShape curve = {
    ArrowPrimaryShape::curve
  };

  constexpr static inline const ArrowShape lcurve = {
    ArrowPrimaryShape::curve, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape rcurve = {
    ArrowPrimaryShape::curve, { ArrowSide::right }
  };

  // -- icurve
  constexpr static inline const ArrowShape icurve = {
    ArrowPrimaryShape::icurve
  };

  constexpr static inline const ArrowShape licurve = {
    ArrowPrimaryShape::icurve, { ArrowSide::left }
  };

  constexpr static inline const ArrowShape ricurve = {
    ArrowPrimaryShape::icurve, { ArrowSide::right }
  };

};  // static struct arrowshapes

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_ARROWTYPE_HPP_
