#pragma once

#include <vector>  // vector

#include <entt.hpp>  // entity, null

#include "wanderer_std.hpp"

namespace wanderer {

struct ButtonGroup final
{
  std::vector<entt::entity> buttons;         ///< The associated button entities.
  entt::entity selected{entt::null};         ///< The currently selected button.
  entt::entity indicator_label{entt::null};  ///< The associated label.
  int32 current_page{};                      ///< The index of the current page.
  int32 items_per_page{};                    ///< Maximum amount of buttons per page.
};

}  // namespace wanderer
