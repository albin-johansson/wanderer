#pragma once

#include <renderer.h>
#include <step.h>

#include <vector>

#include "image_cache.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] auto make_tileset(entt::registry& registry,
                                const std::vector<step::Tileset>& tilesets,
                                ctn::Renderer& renderer,
                                ImageCache& imageCache) -> TilesetEntity;

}
