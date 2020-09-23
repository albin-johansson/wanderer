#pragma once
#include <entt.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::sys {

void update_movement(entt::registry& registry, delta dt);

}  // namespace wanderer::sys
