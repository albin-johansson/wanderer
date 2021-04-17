#pragma once

#include <entt.hpp>  // registry

#include "core/aliases/delta_time.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Time
/// \{

void update_time(entt::registry& registry, delta_time dt);

void render_clock(const entt::registry& registry, graphics_context& graphics);

/// \} End of time

}  // namespace wanderer::sys
