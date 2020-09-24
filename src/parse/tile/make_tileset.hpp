#pragma once

#include <entt.hpp>
#include <memory>  // unique_ptr
#include <renderer.hpp>
#include <step_tileset.hpp>
#include <vector>  // vector

#include "component/tileset.hpp"
#include "image_cache.hpp"

namespace wanderer {

[[nodiscard]] auto make_tileset(
    entt::registry& registry,
    const std::vector<std::unique_ptr<step::tileset>>& tilesets,
    cen::renderer& renderer,
    image_cache& imageCache) -> comp::tileset::entity;

}
