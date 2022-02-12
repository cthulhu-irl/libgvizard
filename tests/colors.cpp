#include "gvizard/colors/rgb.hpp"
#include "gvizard/colors/x11.hpp"
#include <string_view>
#include <catch2/catch.hpp>

#include <gvizard/colors/color.hpp>
#include <gvizard/colors/converter.hpp>
#include <gvizard/utils.hpp>

namespace c = gviz::colors;
using gviz::utils::Converter;

TEST_CASE("[colors::Color]")
{
  c::Color red_a = c::RGB{255, 0, 0};
  c::Color red_b = c::RGBA{255, 0, 0, 255};

  REQUIRE(red_a == red_b);
  REQUIRE(red_a == c::RGB::make(255, 0, 0));
}

// TODO add SchemeColor
TEST_CASE("[colors::Converter]")
{
  c::Color        color   = c::RGB(255, 0, 0);
  c::RGB          rgb     = c::RGB(255, 0, 0);
  c::RGBA         rgba    = c::RGBA(255, 0, 0, 255);
  c::HSV          hsv     = c::HSV(0.f, 1.f, 1.f);
  c::X11Color     x11     = c::X11ColorEnum::red;
  c::SVGColor     svg     = c::SVGColorEnum::red;
  c::X11ColorEnum x11enum = c::X11ColorEnum::red;
  c::SVGColorEnum svgenum = c::SVGColorEnum::red;

  // to color
  REQUIRE(Converter<c::Color,        c::Color>::convert(color)   == color);
  REQUIRE(Converter<c::RGB,          c::Color>::convert(rgb)     == color);
  REQUIRE(Converter<c::RGBA,         c::Color>::convert(rgba)    == color);
  REQUIRE(Converter<c::HSV,          c::Color>::convert(hsv)     == color);
  REQUIRE(Converter<c::X11Color,     c::Color>::convert(x11)     == color);
  REQUIRE(Converter<c::SVGColor,     c::Color>::convert(svg)     == color);
  REQUIRE(Converter<c::X11ColorEnum, c::Color>::convert(x11enum) == color);
  REQUIRE(Converter<c::SVGColorEnum, c::Color>::convert(svgenum) == color);

  // to rgb
  REQUIRE(Converter<c::Color,        c::RGB>::convert(color)   == rgb);
  REQUIRE(Converter<c::RGB,          c::RGB>::convert(rgb)     == rgb);
  REQUIRE(Converter<c::RGBA,         c::RGB>::convert(rgba)    == rgb);
  REQUIRE(Converter<c::HSV,          c::RGB>::convert(hsv)     == rgb);
  REQUIRE(Converter<c::X11Color,     c::RGB>::convert(x11)     == rgb);
  REQUIRE(Converter<c::SVGColor,     c::RGB>::convert(svg)     == rgb);
  REQUIRE(Converter<c::X11ColorEnum, c::RGB>::convert(x11enum) == rgb);
  REQUIRE(Converter<c::SVGColorEnum, c::RGB>::convert(svgenum) == rgb);

  // to rgba
  REQUIRE(Converter<c::Color,        c::RGBA>::convert(color)   == rgba);
  REQUIRE(Converter<c::RGB,          c::RGBA>::convert(rgb)     == rgba);
  REQUIRE(Converter<c::RGBA,         c::RGBA>::convert(rgba)    == rgba);
  REQUIRE(Converter<c::HSV,          c::RGBA>::convert(hsv)     == rgba);
  REQUIRE(Converter<c::X11Color,     c::RGBA>::convert(x11)     == rgba);
  REQUIRE(Converter<c::SVGColor,     c::RGBA>::convert(svg)     == rgba);
  REQUIRE(Converter<c::X11ColorEnum, c::RGBA>::convert(x11enum) == rgba);
  REQUIRE(Converter<c::SVGColorEnum, c::RGBA>::convert(svgenum) == rgba);

  // to hsv
  REQUIRE(Converter<c::Color,        c::HSV>::convert(color)   == hsv);
  REQUIRE(Converter<c::RGB,          c::HSV>::convert(rgb)     == hsv);
  REQUIRE(Converter<c::RGBA,         c::HSV>::convert(rgba)    == hsv);
  REQUIRE(Converter<c::HSV,          c::HSV>::convert(hsv)     == hsv);
  REQUIRE(Converter<c::X11Color,     c::HSV>::convert(x11)     == hsv);
  REQUIRE(Converter<c::SVGColor,     c::HSV>::convert(svg)     == hsv);
  REQUIRE(Converter<c::X11ColorEnum, c::HSV>::convert(x11enum) == hsv);
  REQUIRE(Converter<c::SVGColorEnum, c::HSV>::convert(svgenum) == hsv);

  // to x11color
  REQUIRE(Converter<c::X11Color,     c::X11Color>::convert(x11)     == x11);
  REQUIRE(Converter<c::X11ColorEnum, c::X11Color>::convert(x11enum) == x11);

  // to svgcolor
  REQUIRE(Converter<c::SVGColor,     c::SVGColor>::convert(svg)     == svg);
  REQUIRE(Converter<c::SVGColorEnum, c::SVGColor>::convert(svgenum) == svg);

  // to x11enum
  REQUIRE(Converter<c::X11Color, c::X11ColorEnum>::convert(x11) == x11enum);

  // to svgenum
  REQUIRE(Converter<c::SVGColor, c::SVGColorEnum>::convert(svg) == svgenum);
}

TEST_CASE("[colors::RGB]")
{
  auto red = c::RGB{255, 0, 0};

  REQUIRE(red.min() == 0);
  REQUIRE(red.max() == 255);

  REQUIRE(red == c::RGB::make(255, 0, 0));

  REQUIRE(red.to_binary() == 0xFF0000);

  REQUIRE(red == c::RGB::from_binary(0xFF0000));
}

TEST_CASE("[colors::RGBA]")
{
  auto white           = c::RGBA{255, 255, 255};
  auto red             = c::RGBA::make(255, 0, 0).value();
  auto transparent     = c::RGBA{0, 0, 0, 0};
  auto red_transparent = c::RGBA{255, 0, 0, 0};

  REQUIRE(red == c::RGBA::make(255, 0, 0));
  REQUIRE(white != red);
  REQUIRE(transparent != red_transparent);

  REQUIRE(red.min() == 0);
  REQUIRE(red.max() == 255);
  REQUIRE(white.min() == 255);
  REQUIRE(white.max() == 255);
  REQUIRE(transparent.min() == 0);
  REQUIRE(transparent.max() == 0);

  REQUIRE(red.to_binary() == 0xFFFF0000);
  REQUIRE(white.to_binary() == 0xFFFFFFFF);
  REQUIRE(transparent.to_binary() == 0);
  REQUIRE(red_transparent.to_binary() == 0xFF0000);

  REQUIRE(red == c::RGBA::from_binary(0xFFFF0000));
  REQUIRE(white == c::RGBA::from_binary(0xFFFFFFFF));
  REQUIRE(transparent == c::RGBA::from_binary(0));
  REQUIRE(red_transparent == c::RGBA::from_binary(0xFF0000));
}

TEST_CASE("[colors::svg]")
{
  auto aliceblue = c::SVGColor(c::SVGColorEnum::aliceblue);
  auto cyan      = c::SVGColor(c::SVGColorEnum::cyan);
  
  REQUIRE(aliceblue.get_enum() == c::SVGColorEnum::aliceblue);
  REQUIRE(cyan.get_enum()      == c::SVGColorEnum::cyan);

  REQUIRE(aliceblue.get_name() == std::string_view("aliceblue"));
  REQUIRE(cyan.get_name()      == std::string_view("cyan"));
}

TEST_CASE("[colors::x11]")
{
  auto azure = c::X11Color(c::X11ColorEnum::azure);
  auto brown = c::X11Color(c::X11ColorEnum::brown);
  
  REQUIRE(azure.get_enum() == c::X11ColorEnum::azure);
  REQUIRE(brown.get_enum() == c::X11ColorEnum::brown);

  REQUIRE(azure.get_name() == std::string_view("azure"));
  REQUIRE(brown.get_name() == std::string_view("brown"));
}

