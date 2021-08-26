#ifndef GVIZARD_ATTRS_COMMENT_HPP_
#define GVIZARD_ATTRS_COMMENT_HPP_

#include <string>

#include <gvizard/attribute.hpp>

namespace gvizard::attrs {

struct Comment final : public AttributeBase<Comment, std::string> {
  using value_type = std::string;

  constexpr static const char * const name = "comment";

  explicit Comment() noexcept : AttributeBase() {}
  explicit Comment(const value_type& value) : AttributeBase(value) {}
  explicit Comment(value_type&& value)
    : AttributeBase(std::move(value))
  {}

  static value_type get_default_value() noexcept { return {}; }

  static bool is_default(const value_type& value) noexcept
  {
    return value.size() == 0;
  }

  constexpr static bool constraint(const value_type&) noexcept
  {
    return true;
  }
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRS_COMMENT_HPP_
