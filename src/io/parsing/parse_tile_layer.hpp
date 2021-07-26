#pragma once

#include <rune.hpp>  // tmx_map, tmx_tile_layer, tmx_properties

#include "io/parsing/parse_ir.hpp"

namespace wanderer {

void parse_tile_layer(ir::level& data,
                      const rune::tmx_map& map,
                      const rune::tmx_tile_layer& layer,
                      const rune::tmx_properties& properties,
                      int zIndex);

}
