#pragma once

#include <entt.hpp>

#include "player.hpp"

namespace wanderer::sys {

void update_portal_triggers(entt::registry& registry, comp::player::entity player);

}  // namespace wanderer::sys
