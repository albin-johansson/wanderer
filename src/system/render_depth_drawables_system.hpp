#pragma once

#include <entt.hpp>
#include <renderer.hpp>

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys
