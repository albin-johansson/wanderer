#pragma once

#include <entt.hpp>  // registry

#include "graphics_context.hpp"
#include "time_of_day.hpp"

namespace wanderer::sys {

void update_lights(entt::registry& registry);

void update_player_light_position(entt::registry& registry);

void render_lights(const entt::registry& registry,
                   const ctx::time_of_day& time,
                   graphics_context& graphics);

// Meant to be used if light simulation is disabled
void render_light_overlay(const ctx::time_of_day& time, graphics_context& graphics);

}  // namespace wanderer::sys
