#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// Creates the saves menu entity
auto create_saves_menu(entt::registry& registry) -> comp::menu::entity;

/// Refreshes the state of the saves menu, e.g. fetches the currently available save files
void update_saves_menu(entt::registry& registry);

/// Increments the current saves button group page index
void increment_saves_button_group_page(entt::registry& registry);

/// Decrements the current saves button group page index
void decrement_saves_button_group_page(entt::registry& registry);

}  // namespace wanderer::sys
