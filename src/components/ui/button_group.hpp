#pragma once

#include <vector>  // vector

#include "button.hpp"
#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct button_group_entity_t;
}

struct button_group final
{
  using entity = entity_type<detail::button_group_entity_t>;

  std::vector<button::entity> buttons;
  button::entity selected;
};

}  // namespace wanderer::comp
