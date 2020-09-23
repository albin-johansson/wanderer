#pragma once

#include <renderer.hpp>
#include <step_types.hpp>
#include <string_view>

#include "component/tilemap.hpp"
#include "image_cache.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer {

[[nodiscard]] auto make_map(entt::registry& registry,
                            const step::fs::path& path,
                            cen::renderer& renderer,
                            image_cache& imageCache) -> comp::tilemap::entity;

}
