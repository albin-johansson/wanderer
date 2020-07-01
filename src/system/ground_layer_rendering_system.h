#pragma once

#include <renderer.h>

#include "render_bounds.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   comp::Tilemap::entity mapEntity,
                   ctn::Renderer& renderer,
                   const comp::RenderBounds& bounds);

}  // namespace wanderer::system::layer
