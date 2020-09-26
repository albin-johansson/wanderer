#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys
