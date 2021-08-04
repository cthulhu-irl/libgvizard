#ifndef GVIZARD_ATTRTYPES_RECT_HPP_
#define GVIZARD_ATTRTYPES_RECT_HPP_

#include <optional>
#include <stdexcept>

namespace gvizard::attrtypes {

class Rect final {
  double llx_;
  double lly_;
  double urx_;
  double ury_;

 public:
  constexpr Rect(double llx, double lly, double urx, double ury)
    : llx_(llx), lly_(lly), urx_(urx), ury_(ury)
  {
    if (llx < 0. || lly < 0. || urx < 0. || ury < 0.)
      throw std::invalid_argument(
              "all Rect values must be greater than 0");
  }

  constexpr static std::optional<Rect>
  make(double llx, double lly, double urx, double ury)
  {
    if (llx < 0. || lly < 0. || urx < 0. || ury < 0.)
      return std::nullopt;

    Rect rect;
    rect.llx_ = llx;
    rect.lly_ = lly;
    rect.urx_ = urx;
    rect.ury_ = ury;

    return rect;
  }

  constexpr double llx() const noexcept { return llx_; }
  constexpr double lly() const noexcept { return lly_; }
  constexpr double urx() const noexcept { return urx_; }
  constexpr double ury() const noexcept { return ury_; }

  constexpr Rect& set_llx(double value) { return safe_set(llx_, value); }
  constexpr Rect& set_lly(double value) { return safe_set(lly_, value); }
  constexpr Rect& set_urx(double value) { return safe_set(urx_, value); }
  constexpr Rect& set_ury(double value) { return safe_set(ury_, value); }

  friend constexpr Rect
  operator+(const Rect& lhs, const Rect& rhs) noexcept
  {
    return Rect{
      lhs.llx_ + rhs.llx_,
      lhs.lly_ + rhs.lly_,
      lhs.urx_ + rhs.urx_,
      lhs.ury_ + rhs.ury_
    };
  }

  friend constexpr Rect
  operator-(const Rect& lhs, const Rect& rhs)
  {
    return Rect{
      lhs.llx_ - rhs.llx_,
      lhs.lly_ - rhs.lly_,
      lhs.urx_ - rhs.urx_,
      lhs.ury_ - rhs.ury_
    };
  }

 private:
  Rect() {}

  constexpr Rect& safe_set(double& dest, double value)
  {
    if (value < 0.)
      throw std::invalid_argument("given value to set is below 0");

    dest = value;
    return *this;
  }
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_RECT_HPP_
