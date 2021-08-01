#ifndef GVIZARD_COLORS_GENERAL_HPP_
#define GVIZARD_COLORS_GENERAL_HPP_

#include <cstdint>
#include <stdexcept>

namespace gvizard::colors {

enum class SchemeEnum : uint8_t {
  X11,
  SVG
};

template <typename ColorT>
struct SchemeColor final {
  using color_type = ColorT;

  const char *name   = nullptr;
  color_type  color{};
  SchemeEnum  scheme = SchemeEnum::X11;

  constexpr operator color_type() const
    noexcept(noexcept(color_type(color)))
  {
    return color;
  }
};

template <typename ColorT>
class WeightedColor final {
 public:
  using color_type = ColorT;

 private:
  color_type color_;
  double     weight_;

 public:
  constexpr WeightedColor(ColorT color, double weight)
    : color_(color), weight_(weight)
  {
    if (0. > weight_ || weight_ > 1.)
      throw std::invalid_argument("given weight is out of range. (0, 1)");
  }

  constexpr double get_color() const noexcept(noexcept(color_type(color_)))
  {
    return color_;
  }

  constexpr double get_weight() const noexcept { return weight_; }

  constexpr WeightedColor& set_color(const color_type& color)
  {
    color_ = color;
  }

  constexpr WeightedColor& set_weight(double weight)
  {
    if (0. > weight || weight > 1.)
      throw std::invalid_argument("given weight is out of range. (0, 1)");

    weight_ = weight;
  }
};

}  // namespace gvizard::colors

#endif  // GVIZARD_COLORS_GENERAL_HPP_
