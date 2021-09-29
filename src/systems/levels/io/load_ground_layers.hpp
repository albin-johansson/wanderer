#pragma once

#include <entt.hpp>  // registry

#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void add_ground_layers(entt::registry& registry, const ir::level& data);

}  // namespace wanderer::sys
