#pragma once

#include <entt.hpp>
#include <step_types.hpp>

#include "graphics_context.hpp"
#include "tilemap.hpp"

namespace wanderer {

[[nodiscard]] auto parse_map(entt::registry& registry,
                             const step::fs::path& path,
                             graphics_context& graphics)
    -> comp::tilemap::entity;

}
