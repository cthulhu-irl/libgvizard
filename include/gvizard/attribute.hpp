#ifndef GVIZARD_ATTRIBUTE_HPP_
#define GVIZARD_ATTRIBUTE_HPP_

#include <stdexcept>
#include <string_view>
#include <optional>

namespace gvizard::attrs {

class IAttribute {
 public:
   virtual auto get_name() const noexcept -> const std::string_view = 0;
   virtual bool is_default() const = 0;
   virtual void reset() = 0;
};

template <typename Derived, typename Value>
class AttributeBase : public IAttribute {
  using value_type = Value;

 public:
  AttributeBase() : value_(Derived::get_default_value()) {}
  AttributeBase(value_type value) : value_(Derived::get_default_value()) {
    if (!Derived::constraint(value))
      throw std::runtime_error("attribute constraint unmet");

    value_ = std::move(value);
  }

  static std::optional<Derived> make(value_type value)
  {
    if (!Derived::constraint(value))
      return std::nullopt;

    Derived attr{};
    attr.value_ = std::move(value);
    return attr;
  }

  auto get_name() const noexcept -> const std::string_view override
  {
    return Derived::name;
  }

  bool is_default() const override
  {
    return value_ == get_default();
  }

  void reset() override
  {
    value_ = Derived::get_default_value();
  }

  value_type get_value() &       { return value_; }
  value_type get_value() const&  { return value_; }
  value_type get_value() &&      { return std::move(value_); }
  value_type get_value() const&& { return std::move(value_); }

  value_type get_default() const { return Derived::get_default_value(); }

  auto set_value(value_type value) -> std::optional<const value_type&>
  {
    if (!Derived::constraint(value))
      return std::nullopt;

    value_ = std::move(value);

    return value_;
  }

  operator value_type() const { return value_; }

 protected:
  value_type value_;
};

}  // namespace gvizard::attrs

#endif  // GVIZARD_ATTRIBUTE_HPP_
