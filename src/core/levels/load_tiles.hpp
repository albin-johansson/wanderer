#pragma once

#include <entt.hpp>  // registry
#include <map>       // map

#include "components/tileset.hpp"
#include "core/aliases/tile_id.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

void load_tiles(entt::registry& registry,
                comp::tileset& tileset,
                const graphics_context& graphics,
                const std::map<tile_id, ir::tile>& tiles);

}  // namespace wanderer
