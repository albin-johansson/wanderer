#pragma once

#include <step_map.hpp>  // map

#include "io/map/parse_ir.hpp"

namespace wanderer {

void parse_layers(const step::map& stepMap, ir::level& data);

}  // namespace wanderer
