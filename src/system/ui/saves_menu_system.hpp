#pragma once

#include <cen/key_state.hpp>    // key_state
#include <cen/mouse_state.hpp>  // mouse_state
#include <entt.hpp>             // registry, dispatcher

#include "menu.hpp"

namespace wanderer::sys {

auto create_saves_menu(entt::registry& registry) -> comp::menu::entity;

void refresh_saves_menu(entt::registry& registry);

}  // namespace wanderer::sys
