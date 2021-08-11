#pragma once

#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

namespace wanderer::sys {

void update_plants(entt::registry& registry, rune::delta_time dt);

}  // namespace wanderer::sys
