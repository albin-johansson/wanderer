#pragma once

#include <renderer.hpp>

#include "render_bounds.hpp"
#include "tilemap.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::layer {

void render_ground(entt::registry& registry,
                   comp::Tilemap::entity mapEntity,
                   cen::renderer& renderer,
                   const comp::RenderBounds& bounds);

}  // namespace wanderer::sys::layer
