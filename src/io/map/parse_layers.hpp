#pragma once

#include <step_map.hpp>

#include "parse_ir.hpp"

namespace wanderer {

void parse_layers(const step::map& stepMap, ir::level& data);

}  // namespace wanderer
