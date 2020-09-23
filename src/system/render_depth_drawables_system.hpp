#pragma once

#include <renderer.hpp>

#include "wanderer_stdinc.h"

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys
