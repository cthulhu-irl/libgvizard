#ifndef GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_
#define GVIZARD_ATTRTYPES_SHAPE_RECORD_HPP_

#include <string>
#include <vector>
#include <variant>

struct RecordFieldId final {
  std::string name{};
  std::string port{};
};

template <typename First, typename ...Rest>
using first_parameter_pack_t = First;

struct RecordShape final {
  using fieldid_list_type = std::vector<RecordFieldId>;
  using field_type = std::variant<RecordFieldId, fieldid_list_type>;

  std::vector<field_type> fields{};

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
