#pragma once

#include <renderer.hpp>
#include <step_tileset.hpp>
#include <vector>

#include "image_cache.h"
#include "tileset.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] auto make_tileset(
    entt::registry& registry,
    const std::vector<std::unique_ptr<step::tileset>>& tilesets,
    cen::renderer& renderer,
    image_cache& imageCache) -> comp::Tileset::entity;

}
