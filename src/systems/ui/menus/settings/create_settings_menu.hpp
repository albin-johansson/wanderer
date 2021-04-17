#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// Creates the setting menu entity
auto create_settings_menu(entt::registry& registry) -> comp::menu::entity;

}  // namespace wanderer::sys
