#pragma once

#include <vector>  // vector

#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct button_group_entity_t;
}

struct button_group final
{
  using entity = entity_type<detail::button_group_entity_t>;

  std::vector<button::entity> buttons;
  button::entity selected{null<button>()};
  label::entity indicator_label{null<label>()};  ///< Reference to associated label
  int current_page{};                            ///< The index of the current page
  int items_per_page{};                          ///< Maximum amount of buttons per page
};

}  // namespace wanderer::comp
