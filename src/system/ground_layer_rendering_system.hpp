#pragma once

#include <renderer.hpp>

#include "render_bounds.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::layer {

void render_ground(entt::registry& registry,
                   comp::Tilemap::entity mapEntity,
                   cen::renderer& renderer,
                   const comp::RenderBounds& bounds);

}  // namespace wanderer::sys::layer
