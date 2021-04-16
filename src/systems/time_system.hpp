#pragma once

#include <entt.hpp>  // registry

#include "delta_time.hpp"
#include "graphics_context.hpp"

namespace wanderer::sys {

void update_time(entt::registry& registry, delta_time dt);

void render_clock(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
