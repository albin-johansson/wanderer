#pragma once

#include <entt.hpp>

#include "menu.hpp"

namespace wanderer::sys {

auto create_settings_menu(entt::registry& registry) -> comp::menu::entity;

}
