#pragma once

#include <entt.hpp>

#include "aabb_tree.hpp"
#include "parse_ir.hpp"
#include "tileset.hpp"

namespace wanderer {

void add_tile_objects(entt::registry& registry,
                      aabb_tree& tree,
                      const ir::level& levelData,
                      const comp::tileset& tileset);

}
