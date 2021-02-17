#pragma once

#include <entt.hpp>

#include "parse_ir.hpp"
#include "tileset.hpp"

namespace wanderer {

[[nodiscard]] auto create_tileset(const std::vector<ir::tileset>& data,
                                  entt::registry& registry,
                                  comp::tileset::entity entity)
    -> comp::tileset&;

}
