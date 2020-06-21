/**
 * This file declares the systems associated with rendering tile layers.
 *
 * @namespace wanderer::system::layer
 * @file layer_rendering_system.h
 */

#pragma once

#include <renderer.h>

#include "render_bounds.h"
#include "tile_layer.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::layer {

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
            const TileLayer& layer,
            centurion::Renderer& renderer,
            const Tileset& tileset,
            const RenderBounds& bounds);

}  // namespace wanderer::system::layer
