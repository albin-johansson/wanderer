#pragma once

#include <entt.hpp>  // registry

#include "core/graphics_context.hpp"
#include "ctx/settings.hpp"
#include "ctx/time_of_day.hpp"

namespace wanderer::sys {

void update_lights(entt::registry& registry);

void update_player_light_position(entt::registry& registry);

void render_lights(const entt::registry& registry,
                   graphics_context& graphics,
                   const ctx::time_of_day& time,
                   const ctx::settings& settings);

}  // namespace wanderer::sys
