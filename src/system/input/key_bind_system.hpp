#pragma once

#include <cen/scan_code.hpp>  // scan_code
#include <entt.hpp>           // registry

#include "key_bind.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

auto make_bind(entt::registry& registry, cen::scan_code key, menu_action action)
    -> comp::key_bind::entity;

}
