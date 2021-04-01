#pragma once

#include <entt.hpp>

#include "parse_ir.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

namespace wanderer {

[[nodiscard]] auto create_tilemap(const ir::level& data,
                                  entt::registry& registry,
                                  comp::tilemap::entity entity,
                                  comp::tileset::entity tileset) -> comp::tilemap&;

}
