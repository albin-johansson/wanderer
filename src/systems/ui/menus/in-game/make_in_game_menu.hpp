#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

auto make_in_game_menu(entt::registry& registry) -> comp::menu::entity;

/// \} End of menus

}  // namespace wanderer::sys