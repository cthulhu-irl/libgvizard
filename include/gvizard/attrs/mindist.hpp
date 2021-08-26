#ifndef GVIZARD_ATTRS_MINDIST_HPP_
#define GVIZARD_ATTRS_MINDIST_HPP_
  
#include <gvizard/attribute.hpp>
  
namespace gvizard::attrs {  
  
struct MinDist final : public AttributeBase<MinDist, double> {
  using value_type = double;  
  
  constexpr static const char * const name = "mindist";
  
  constexpr explicit MinDist() : AttributeBase() {}
  constexpr explicit MinDist(value_type value) : AttributeBase(value) {}
  
  constexpr static value_type get_default_value() noexcept { return 1.; }
  
  constexpr static bool is_default(value_type value) noexcept
  {  
    return value == get_default_value();
  }  
  
  constexpr static bool constraint(value_type value) noexcept
  {  
    return value >= 0.;  
  }  
};  
  
}  // namespace gvizard::attrs 
  
#endif  // GVIZARD_ATTRS_MINDIST_HPP_
