#ifndef GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_
#define GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_

#include <string>
#include <vector>
#include <variant>

namespace gviz::attrtypes {

template <typename NameT = std::string, typename PortT = std::string>
struct RecordFieldId final {
  using name_type = NameT;
  using port_type = PortT;

  name_type name{};
  port_type port{};

  constexpr RecordFieldId(name_type arg_name = {}, port_type arg_port = {})
    : name(std::move(arg_name))
    , port(std::move(arg_port))
  {}
};

template <typename FieldIdT = RecordFieldId<std::string, std::string>,
          template <typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
struct RecordShape final {
  using fieldid_type = FieldIdT;
  using fieldid_list_type = Vec<fieldid_type, VecArgs...>;
  using field_type = std::variant<fieldid_type, fieldid_list_type>;

  Vec<field_type, VecArgs...> fields{};
};

}  // namespace gviz::attrtypes

#endif  // GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_
