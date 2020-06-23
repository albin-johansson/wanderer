#pragma once

#include <renderer.h>

#include "render_bounds.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   component::TilemapEntity mapEntity,
                   centurion::Renderer& renderer,
                   const RenderBounds& bounds);

}  // namespace wanderer::system::layer
