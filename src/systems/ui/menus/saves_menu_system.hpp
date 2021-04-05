#pragma once

#include <centurion.hpp>  // keyboard, mouse
#include <entt.hpp>       // registry, dispatcher

#include "menu.hpp"

namespace wanderer::sys {

auto create_saves_menu(entt::registry& registry) -> comp::menu::entity;

void update_saves_menu(entt::registry& registry);

}  // namespace wanderer::sys
