#pragma once

#include <rune/everything.hpp>  // tmx_map, tmx_tile_layer, tmx_properties

#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

void parse_tile_layer(ir::level& data,
                      const rune::tmx_map& map,
                      const rune::tmx_tile_layer& layer,
                      const rune::tmx_properties& properties,
                      int layerIndex);

}  // namespace wanderer::io
