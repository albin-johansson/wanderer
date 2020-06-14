#pragma once

#include <renderer.h>

#include "render_bounds.h"
#include "types.h"

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   entt::entity mapEntity,
                   centurion::Renderer& renderer,
                   const RenderBounds& bounds);

}  // namespace wanderer::system::layer
