#pragma once

#include <entt.hpp>  // registry

#include "graphics_context.hpp"

namespace wanderer::sys {

void render_debug_info(const entt::registry& registry,
                       graphics_context& graphics);

}  // namespace wanderer::sys
