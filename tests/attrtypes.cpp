#include <catch2/catch.hpp>

#include <gvizard/attrtypes/addible.hpp>
#include <gvizard/attrtypes/escstring.hpp>

using gviz::attrtypes::AddDouble;
using gviz::attrtypes::EscNameSetRef;
using gviz::attrtypes::EscString;

TEST_CASE("[attrtypes::AddDouble]")
{
  AddDouble a = 3;
  AddDouble b = 4;

  REQUIRE(a + b == 7);
  REQUIRE(a - b == -1);
  REQUIRE(a * b == 12);
  REQUIRE(a / b == 3.0/4.0);
  REQUIRE_FALSE(a / b != 3.0/4.0);

  REQUIRE( 7 == a + b);
  REQUIRE(-1 == a - b);
  REQUIRE(12 == a * b);
  REQUIRE(3.0/4.0 == a / b);
  REQUIRE_FALSE(3.0/4.0 != a / b);

  REQUIRE(a != b);
}

TEST_CASE("[attrtypes::EscString]")
{
  const EscString<> empty_escstring = "";

  const EscString<std::string> escstring =
    "\\G as Graph: \\G, Node: \\N, Edge: \\E, "
    "Label: \\L, Head: \\H, Tail: \\T"_escsv;

  const auto escnameset = EscNameSetRef{}.set_graph_str("A Graph")
                                         .set_node_str("A Node")
                                         .set_edge_str("An Edge")
                                         .set_label_str("A Label")
                                         .set_head_str("A Head")
                                         .set_tail_str("A Tail");

  const char* expected_result =
    "A Graph as Graph: A Graph, Node: A Node, Edge: An Edge, "
    "Label: A Label, Head: A Head, Tail: A Tail";

  REQUIRE(escstring.get_occurences().graph == 2);
  REQUIRE(escstring.get_occurences().node  == 1);
  REQUIRE(escstring.get_occurences().edge  == 1);
  REQUIRE(escstring.get_occurences().label == 1);
  REQUIRE(escstring.get_occurences().head  == 1);
  REQUIRE(escstring.get_occurences().tail  == 1);

  REQUIRE(escstring.get_occurences().sum() == 7);

  REQUIRE(escstring.apply(escnameset) == expected_result);

  REQUIRE(EscString<>().apply() == "");
  REQUIRE(empty_escstring.apply() == "");
  REQUIRE(empty_escstring.apply(escnameset) == "");
  REQUIRE(empty_escstring.get_occurences().sum() == 0);
}

TEST_CASE("[attrtypes::PackMode]")
{
  //
}
