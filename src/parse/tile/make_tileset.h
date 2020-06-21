#pragma once

#include <renderer.h>
#include <step.h>

#include <vector>

#include "image_cache.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] TilesetEntity make_tileset(
    entt::registry& registry,
    const std::vector<step::Tileset>& tilesets,
    centurion::Renderer& renderer,
    ImageCache& imageCache);

}
