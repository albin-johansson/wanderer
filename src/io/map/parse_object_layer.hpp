#pragma once

#include <step_map.hpp>

#include "parse_ir.hpp"

namespace wanderer {

void parse_object_layer(ir::level& data,
                        const step::map& stepMap,
                        const step::object_group& group);

}
