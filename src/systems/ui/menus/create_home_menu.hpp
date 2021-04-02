#pragma once

#include <entt.hpp>  // registry

#include "menu.hpp"

namespace wanderer::sys {

auto create_home_menu(entt::registry& registry) -> comp::menu::entity;

}
