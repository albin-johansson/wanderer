#pragma once

#include <entt.hpp>
#include <renderer.hpp>
#include <step_types.hpp>

#include "component/tilemap.hpp"
#include "image_cache.hpp"

namespace wanderer {

[[nodiscard]] auto make_map(entt::registry& registry,
                            const step::fs::path& path,
                            cen::renderer& renderer,
                            image_cache& imageCache) -> comp::tilemap::entity;

}
