#pragma once

#include <entt.hpp>  // registry

#include "components/map/tilemap.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

[[nodiscard]] auto load_tilemap(entt::registry& registry,
                                const comp::tilemap::entity entity,
                                const ir::level& level) -> map_id;
}  // namespace wanderer
