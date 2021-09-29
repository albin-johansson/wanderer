#pragma once

#include <entt.hpp>  // registry

#include "components/tiles/tilemap.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

[[nodiscard]] auto load_tilemap(entt::registry& registry,
                                const comp::tilemap::entity entity,
                                const ir::level& level) -> map_id;
}  // namespace wanderer::sys
