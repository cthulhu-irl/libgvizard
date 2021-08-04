#ifndef GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_
#define GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_

#include <string>
#include <vector>
#include <variant>

template <typename NameT = std::string, typename PortT = std::string>
struct RecordFieldId final {
  using name_type = NameT;
  using port_type = PortT;

  name_type name{};
  port_type port{};
};

template <typename FieldIdT = RecordFieldId<std::string, std::string>,
          template <typename, typename...> typename Vec = std::vector,
          typename ...VecArgs>
struct RecordShape final {
  using fieldid_type = FieldIdT;
  using fieldid_list_type = Vec<fieldid_type, VecArgs...>;
  using field_type = std::variant<fieldid_type, fieldid_list_type>;

  Vec<field_type, VecArgs...> fields{};

  template <typename ...Args>
  RecordShape(const field_type& first, Args&& ...args)
    : fields{first, std::forward<Args>(args)...}
  {}

  template <typename ...Args>
  RecordShape(field_type&& first, Args&& ...args)
    : fields{std::move(first), std::forward<Args>(args)...}
  {}
};

#endif  // GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_
