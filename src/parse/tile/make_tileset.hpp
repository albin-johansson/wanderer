#pragma once

#include <renderer.hpp>
#include <step_tileset.hpp>
#include <vector>

#include "image_cache.hpp"
#include "tileset.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer {

[[nodiscard]] auto make_tileset(
    entt::registry& registry,
    const std::vector<std::unique_ptr<step::tileset>>& tilesets,
    cen::renderer& renderer,
    image_cache& imageCache) -> comp::Tileset::entity;

}
