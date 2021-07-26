#pragma once

#include <rune.hpp>  // tmx_map, tmx_object_layer

#include "io/map/parse_ir.hpp"

namespace wanderer {

void parse_object_layer(ir::level& data,
                        const rune::tmx_map& map,
                        const rune::tmx_object_layer& objectLayer);

}
