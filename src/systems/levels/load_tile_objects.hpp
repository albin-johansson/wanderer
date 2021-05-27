#pragma once

#include "components/map/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer::sys {

void load_tile_objects(comp::level& level,
                       const graphics_context& graphics,
                       const ir::level& levelData);

}  // namespace wanderer::sys
