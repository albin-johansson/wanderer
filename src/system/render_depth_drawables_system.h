#pragma once

#include <renderer.h>

#include "wanderer_stdinc.h"

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, ctn::Renderer& renderer);

}  // namespace wanderer::sys
