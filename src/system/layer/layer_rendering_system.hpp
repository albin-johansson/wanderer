#pragma once

#include <entt.hpp>
#include <renderer.hpp>

#include "component/render_bounds.hpp"
#include "component/tile_layer.hpp"
#include "component/tileset.hpp"

namespace wanderer::sys::layer {

/**
 * Renders a tile layer.
 *
 * @param registry the registry associated with the layer.
 * @param layer the tile layer that will be rendered.
 * @param renderer the renderer that will be used.
 * @param tileset the tileset that will be used to render animated tiles.
 * @param bounds the rendering bounds that will be used.
 */
void render(entt::registry& registry,
            const comp::tile_layer& layer,
            cen::renderer& renderer,
            const comp::tileset& tileset,
            const comp::render_bounds& bounds);

}  // namespace wanderer::sys::layer
