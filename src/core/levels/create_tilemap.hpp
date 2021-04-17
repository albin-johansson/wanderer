#pragma once

#include <entt.hpp>  // registry

#include "components/map/tilemap.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

[[nodiscard]] auto create_tilemap(const ir::level& data,
                                  entt::registry& registry,
                                  comp::tilemap::entity entity) -> comp::tilemap&;

}
