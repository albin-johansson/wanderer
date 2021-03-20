#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "menu.hpp"
#include "menu_id.hpp"

namespace wanderer::sys {

auto make_menu(entt::registry& registry,
               std::string title,
               menu_id id,
               bool blocking = true) -> comp::menu::entity;

}
