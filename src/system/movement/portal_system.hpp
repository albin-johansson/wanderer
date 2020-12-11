#pragma once

#include <entt.hpp>

#include "player.hpp"

namespace wanderer::sys::portal {

void update(entt::registry& registry, comp::player::entity player);

}
