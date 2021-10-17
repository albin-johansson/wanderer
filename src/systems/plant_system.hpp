#pragma once

#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

namespace wanderer::sys {

void UpdatePlants(entt::registry& registry, float dt);

}  // namespace wanderer::sys
