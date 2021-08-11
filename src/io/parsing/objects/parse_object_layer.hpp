#pragma once

#include <rune/everything.hpp>  // tmx_map, tmx_object_layer

#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

void parse_object_layer(ir::level& data,
                        const rune::tmx_map& map,
                        const rune::tmx_object_layer& objectLayer);

}  // namespace wanderer::io
