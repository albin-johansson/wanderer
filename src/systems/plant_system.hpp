#pragma once

#include <entt/entt.hpp>  // registry
#include <rune/rune.hpp>  // delta_time

namespace wanderer::sys {

void UpdatePlants(entt::registry& registry, float dt);

}  // namespace wanderer::sys
