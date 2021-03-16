#pragma once

#include <entt.hpp>

#include "aabb_tree.hpp"
#include "graphics_context.hpp"
#include "parse_ir.hpp"
#include "tileset.hpp"

namespace wanderer {

void add_tile_objects(entt::registry& registry,
                      aabb_tree& tree,
                      const graphics_context& graphics,
                      const ir::level& levelData,
                      const comp::tileset& tileset);

}
