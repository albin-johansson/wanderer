#pragma once

#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void LoadTilesetTextures(const ir::level& data, GraphicsContext& graphics);

}  // namespace wanderer::sys
