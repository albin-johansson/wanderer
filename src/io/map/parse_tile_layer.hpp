#pragma once

#include <step_map.hpp>

#include "parse_ir.hpp"

namespace wanderer {

void parse_tile_layer(ir::level& data,
                      const step::map& stepMap,
                      const step::tile_layer& stepLayer,
                      const step::properties* layerProperties,
                      int zIndex);

}
