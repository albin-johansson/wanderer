#pragma once

#include "components/lvl/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void load_tile_objects(comp::Level& level,
                       const graphics_context& graphics,
                       const ir::level& levelData);

}  // namespace wanderer::sys
