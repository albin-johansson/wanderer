#pragma once

#include <rune.hpp>  // tmx_map

#include "io/map/parse_ir.hpp"

namespace wanderer {

void parse_layers(const rune::tmx_map& map, ir::level& data);

}  // namespace wanderer
