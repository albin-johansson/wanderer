#pragma once

#include <entt.hpp>  // registry

#include "core/aliases/aabb_tree.hpp"
#include "core/graphics_context.hpp"
#include "ctx/tileset.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

void add_tile_objects(entt::registry& registry,
                      aabb_tree& tree,
                      const graphics_context& graphics,
                      const ir::level& levelData,
                      const ctx::tileset& tileset);

}
