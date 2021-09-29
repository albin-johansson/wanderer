#pragma once

#include <rune/everything.hpp>  // tmx_map

#include "io/tmx/parse_ir.hpp"

namespace wanderer::io {

void parse_layers(const rune::tmx_map& map, ir::level& data);

}  // namespace wanderer::io
