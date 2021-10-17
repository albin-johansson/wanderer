#pragma once

#include <entt.hpp>  // registry
#include <map>       // map
#include <vector>    // vector

#include "components/tiles/tileset.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void LoadTileset(entt::registry& registry,
                 const entt::entity tilesetEntity,
                 const GraphicsContext& graphics,
                 const std::vector<ir::tileset>& data);

}  // namespace wanderer::sys
