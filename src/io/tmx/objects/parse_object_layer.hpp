#pragma once

#include <rune/everything.hpp>  // tmx_object_layer

#include "io/tmx/parse_ir.hpp"

namespace wanderer::io {

void parse_object_layer(ir::level& data, const rune::tmx_object_layer& objectLayer);

}  // namespace wanderer::io
