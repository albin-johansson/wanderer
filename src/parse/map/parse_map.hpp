#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>
#include <step_types.hpp>

#include "texture_cache.hpp"
#include "tilemap.hpp"

namespace wanderer {

[[nodiscard]] auto parse_map(entt::registry& registry,
                             const step::fs::path& path,
                             cen::renderer& renderer,
                             texture_cache& imageCache)
    -> comp::tilemap::entity;

}
