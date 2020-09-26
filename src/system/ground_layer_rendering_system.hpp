#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

#include "component/render_bounds.hpp"
#include "component/tilemap.hpp"

namespace wanderer::sys::layer {

void render_ground(entt::registry& registry,
                   comp::tilemap::entity map,
                   cen::renderer& renderer,
                   const comp::render_bounds& bounds);

}  // namespace wanderer::sys::layer
