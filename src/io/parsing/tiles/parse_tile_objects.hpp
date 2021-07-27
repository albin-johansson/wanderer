#pragma once

#include "io/parsing/common.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

void parse_tile_objects(ir::level& data, const tile_data& tiles, int layerIndex);

}  // namespace wanderer::io
