#pragma once

#include "core/graphics/graphics_context.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics);

}  // namespace wanderer
