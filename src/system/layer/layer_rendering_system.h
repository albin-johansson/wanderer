#pragma once

#include <renderer.h>

#include "render_bounds.h"
#include "tile_layer.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::layer {

void render(entt::registry& registry,
            const TileLayer& layer,
            centurion::Renderer& renderer,
            const Tileset& tileset,
            const RenderBounds& bounds);

}
