#pragma once

#include <entt.hpp>

#include "parse_ir.hpp"

namespace wanderer {

void add_ground_layers(entt::registry& registry, const ir::level& data);

}
