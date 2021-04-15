#pragma once

#include <vector>  // vector

#include "button.hpp"
#include "entity_type.hpp"
#include "label.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct button_group_entity_t;
}

struct button_group final
{
  using entity = entity_type<detail::button_group_entity_t>;

  std::vector<button::entity> buttons;

  button::entity selected{null<button>()};
  label::entity indicatorLabel{null<label>()};  ///< Reference to associated label

  int currentPage{};   ///< The index of the current page
  int itemsPerPage{};  ///< The maximum amount of buttons per page
};

}  // namespace wanderer::comp
