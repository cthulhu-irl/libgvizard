#ifndef GVIZARD_ATTRTYPES_SHAPE_HPP_
#define GVIZARD_ATTRTYPES_SHAPE_HPP_

#include <cstdint>

namespace gvizard::attrtypes {

enum class ShapeType : uint8_t {
  ellipse = 0,
  none,  // user-defined shape
  box,
  polygon,
  oval,
  circle,
  point,
  egg,
  traingle,
  plaintext,
  plain,
  diamond,
  trapezium,
  parallelogram,
  house,
  pentagon,
  hexagon,
  septagon,
  octagon,
  doublecircle,
  doubleoctagon,
  tripleoctagon,
  invtriangle,
  invtrapezium,
  invhouse,
  Mdiamond,
  Msquare,
  Mcircle,
  rect,
  rectangle,
  square,
  star,
  underline,
  cylinder,
  note,
  tab,
  folder,
  box3d,
  component,
  promoter,
  cds,
  terminator,
  utr,
  primersite,
  restrictionsite,
  fivepoverhang,
  threepoverhang,
  noverhang,
  assembly,
  signature,
  insulator,
  ribosite,
  rnastab,
  proteasesite,
  proteinstab,
  rpromoter,
  rarrow,
  larrow,
  lpromoter,

  record,  // record-based shape
  Mrecord  // record-based shape with rounded edges
};

}  // namespace gvizard::attrtypes

#endif  // GVIZARD_ATTRTYPES_SHAPE_HPP_
