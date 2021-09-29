#pragma once

#include <entt.hpp>  // registry
#include <map>       // map
#include <vector>    // vector

#include "components/tiles/tileset.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void load_tileset(entt::registry& registry,
                  const entt::entity tilesetEntity,
                  const graphics_context& graphics,
                  const std::vector<ir::tileset>& data);

}  // namespace wanderer::sys
