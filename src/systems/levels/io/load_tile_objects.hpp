#pragma once

#include "components/lvl/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void LoadTileObjects(comp::Level& level,
                     const GraphicsContext& graphics,
                     const ir::level& levelData);

}  // namespace wanderer::sys
