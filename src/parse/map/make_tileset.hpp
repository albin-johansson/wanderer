#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>
#include <memory>  // unique_ptr
#include <step_tileset.hpp>
#include <vector>  // vector

#include "texture_cache.hpp"
#include "tileset.hpp"

namespace wanderer {

using tileset_collection = std::vector<std::unique_ptr<step::tileset>>;

[[nodiscard]] auto make_tileset(entt::registry& registry,
                                const tileset_collection& tilesets,
                                cen::renderer& renderer,
                                texture_cache& imageCache)
    -> comp::tileset::entity;

}  // namespace wanderer
