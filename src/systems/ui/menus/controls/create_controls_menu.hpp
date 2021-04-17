#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

auto create_controls_menu(entt::registry& registry) -> comp::menu::entity;

/// \} End of menus

}
