#pragma once

#include <entt.hpp>

#include "player.hpp"

namespace wanderer::sys::inventory {

void update_triggers(entt::registry& registry, comp::player::entity player);

}
