#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

#include "render_bounds.hpp"
#include "tile_layer.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

namespace wanderer::sys::layer {

/**
 * Renders a tile layer.
 *
 * \param registry the registry associated with the layer.
 * \param layer the tile layer that will be rendered.
 * \param renderer the renderer that will be used.
 * \param tileset the tileset that will be used to render animated tiles.
 * \param bounds the rendering bounds that will be used.
 */
void render(const entt::registry& registry,
            const comp::tile_layer& layer,
            cen::renderer& renderer,
            const comp::tileset& tileset,
            const comp::render_bounds& bounds);

/**
 * \brief Renders all of the ground layers in a map.
 *
 * \param registry the registry that holds the layers.
 * \param map the map that holds the ground layers that will be rendered.
 * \param renderer the renderer that will be used.
 * \param bounds the render bounds that will be used.
 *
 * \since 0.1.0
 */
void render_ground(const entt::registry& registry,
                   comp::tilemap::entity map,
                   cen::renderer& renderer,
                   const comp::render_bounds& bounds);

}  // namespace wanderer::sys::layer
