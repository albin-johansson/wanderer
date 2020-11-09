#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>
#include <memory>  // unique_ptr
#include <step_tileset.hpp>
#include <vector>  // vector

#include "component/tileset.hpp"
#include "texture_cache.hpp"

namespace wanderer {

[[nodiscard]] auto make_tileset(
    entt::registry& registry,
    const std::vector<std::unique_ptr<step::tileset>>& tilesets,
    cen::renderer& renderer,
    texture_cache& imageCache) -> comp::tileset::entity;

}
