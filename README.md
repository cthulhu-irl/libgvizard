# libgvizard

libgvizard is a c++17 header-only graph visualization abstraction library that only provides a comprehensive flexible set of types and interfaces heavily inspired by graphviz, along with visualization attributes, graph and related data structures, and other utilities.

upon this library, many can make different renderers and thus one with a single graph definition can render it by different renderers of choice.

### Requirements
  - EnTT
  - magic-enum
  - catch2 (optional: for tests)

if vcpkg build toolchain isn't specified, the packages will be automatically downloaded on cmake build.

### Build tests and examples

if you already have vcpkg, specify it with `-DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake`.

```bash
mkdir build && cd build
cmake ..
make
```

to test:
```
ctest --output-on-failure
```

to run a specific example:
```
./examples/simple_dot_generator/simple_dot_generator
```

### Usage exampe

a glare of some parts of the api:
```cpp
using NodeName = typename MyRenderer::NodeName;

auto make_graph()
{
  gviz::GvizGraph<> ret{};

  auto node_a = ret.graph.create_node();
  auto node_b = ret.graph.create_node();
  auto node_c = ret.graph.create_node();
  auto node_d = ret.graph.create_node();

  ret.graph.set_entity_attr<NodeName>(node_a, NodeName{"a"});
  ret.graph.set_entity_attr<NodeName>(node_b, NodeName{"b"});
  ret.graph.set_entity_attr<NodeName>(node_c, NodeName{"c"});
  ret.graph.set_entity_attr<NodeName>(node_d, NodeName{"d"});

  ret.graph.create_edge(node_a, node_b);
  ret.graph.create_edge(node_c, node_d);

  ret.set_node_label(node_a, gviz::attrtypes::Label<>("This is Node A"));
  ret.set_node_label(node_a, gviz::attrtypes::Label<>("This is Node D"));

  ret.set_node_style(node_a, gviz::attrtypes::CommonStyle::bold);
  ret.set_node_style(node_b, gviz::attrtypes::CommonStyle::dashed);
  ret.set_node_style(node_c, gviz::attrtypes::CommonStyle::dotted);

  return ret;
}
```

### Overview
  - What problem does it solve?

    many graph implementations that I could find were either focused on being
    performant and general as they can, or machine learning.
   
    this library though is both focused on visualization aspects and
    is very flexible/modular as in interface-oriented and generic,
    and uses registry alongside graph data structure sharing a unique id
    for each entity (node, edge, cluster), to be used to set/unset
    different attributes by type.

  - How does it work?

    There are 5 main components:
    `GvizGraph`, `Graph`, `Registry`, `Attribute`, `AttributeType`
    
    The word `entity` refers to node, edge or cluster and is basically just
    an identifier along with its holden storage for set types that is
    created/destroyed and its id is used to access its underlying
    holden storage in `Registry`.
   
    `GvizGraph` is what puts all other components together
    along with helper methods,
    consisting of `Graph` data structure itself (which contains its registry)
    and a `registry entity proxy` (same registry methods that don't
    take an entity id and forward the args along with `entity id` given at
    construction to the shared registry container at `graph`) for each
    entity type (node, edge, cluster) that hold global values for
    an `Attribute`, which according to graphviz is used for an entity when
    that `Attribute` isn't set for an entity of same type.
   
    `Graph` is the data structure holding the hierarchy of the graph,
    having nodes, edges (which connect two nodes to each other), and cluster
    (which can contain zero or more nodes but two clusters never share a node).
    the `Graph` is also in charge of holding its `Registry` and provide
    access/modifier methods to get/set/remove an `Attribute`
    from/to an entity.
   
    `Registry` is a set of entities each with a unique id mapped to
    limited or unlimited set of types which are accessed/modifed by
    a pair of `entity id` and `value type`
    (thus an entity can't contain two values for same type).
    this `type` is commonly an `Attribute`, but it's not enforced and
    it's up to renderer what types to accepts and how behave about it.
   
    an `Attribute` supposedly defines appearance of an entity and consists
    of a name, a default value and the set value, the type of this value
    is an `AttributeType`. the type can be variant and accept serveral
    `AttributeTypes`.
    The resulting appearance after render is up to renderer and
    this library doesn't guarantee that.

    (this library provides all attributes defined in graphviz documentation)

    `AttributeType` is a type that is used by an `Attribute` to define
    appearance of an entity. such as `Style`, `Shape` or `Color`.

    (this library provides all attrtibute types defined in graphviz documentation)

  - General utilities:
    - `Color`: `RGB`, `RGBA`, `HSV` colors
      and `X11Color`, `SGVColor` color schemes.
      all convertible to each other using `Converter` utility.

    - `Converter`: one-way conversion interface/struct where to conversion of
      type `T` to type `U` can be defined by writing a template specification of
      it and defining `convert` method which can be overloaded too.

    - `EnumHelper`: a reflection-like utility to get an enum value by its
      underlying value, field name, or index. also vice versa.

    - `LambdaVisitor`: a simple utility that takes one or more
      lambda (or any struct/class based callable, not function) instances,
      and makes a single overloaded callable.
      it comes very handy when dealing with `std::variant` by `std::visit`.

    - `LambdaVisit`: takes a visitable and one or more callables that
      `LambdaVisitor` accepts and
      returns `std::visit(LambdaVisitor{ callables... }, visitable)`.

    - `OptionalRef`: a `std::optional<T&>`, taking a `T` and holding
      a pointer to its original address or `nulloptref` to hold a null pointer.

    - `Contract`: a monad-like single container that holds a value
      that satisfies a given predicate.
      used as `Contract<T, auto callable_predicate>`.

  - Template Meta-Programming utilites:
    - `all_unique<typename ...Types>`:
      checks each type `T` in `Types` against all other type `U` in `Types`
      by `!std::is_same_v<T, U>`.

    - `all_unique<typename Base, typename ...Types>`:

      all `T` from Types must satisfy `std::is_base_of<Base, T>`
    - `always<typename T>`: having `auto f = always<int>{42};`, calling f by any argument returns `42`, `f(x) == 42`.

    - `Expandable<typename ...Ts>`: provides `expand_for_t<Consumer, ...Us>`
      which makes the type `Consumer<Ts..., Us...>`.
      similarly `rexpand_for_t` makes `Consumer<Us..., Ts...>`.

    - `TypeInfo<typename T, typename ...Ts>`: contains types `first = T`
      and constexpr static value `rest = TypeInfo<Ts...>{}`, along with
      `size = 1 + sizeof...(Ts)`.

    - `MixTypeInfo<typename ...TypeInfos>`: combines several `TypeInfo<...Ts>`
      into a single `TypeInfo`.
      for example
        `MixTypeInfo<TypeInfo<A, B, C>, TypeInfo<D, E>, TypeInfo<F>>::type`
      is same as `TypeInfo<A, B, C, D, E, F>`.

    - `PackDrop<std::size_t I, typename ...Ts>`:
      drops `I` many types from `Ts...`
      and storing the rest as `type = TypeInfo<Us...>`.

    - `find_type_index_in<typename X, typename ...Ts>`:
      finds index of `X` in `Ts...` plus 1, having 0 reserved as not found.

    - `has_type_in<typename X, typename ...Ts>`: checks if `X` is in `Ts...`.
