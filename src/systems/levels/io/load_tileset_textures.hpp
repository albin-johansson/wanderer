#pragma once

#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void load_tileset_textures(const ir::level& data, graphics_context& graphics);

}  // namespace wanderer::sys
