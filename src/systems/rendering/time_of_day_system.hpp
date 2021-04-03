#pragma once

#include <entt.hpp>  // registry

#include "delta.hpp"
#include "graphics_context.hpp"

namespace wanderer::sys {

void update_time_of_day(entt::registry& registry, delta_t dt);

void render_clock(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
