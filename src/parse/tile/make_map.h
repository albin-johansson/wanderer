#pragma once

#include <renderer.hpp>
#include <step_types.hpp>
#include <string_view>

#include "image_cache.h"
#include "tilemap.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] auto make_map(entt::registry& registry,
                            const step::fs::path& path,
                            cen::renderer& renderer,
                            image_cache& imageCache) -> comp::Tilemap::entity;

}
