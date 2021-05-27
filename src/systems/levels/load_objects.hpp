#pragma once

#include <entt.hpp>  // registry

#include "io/map/parse_ir.hpp"

namespace wanderer::sys {

void load_objects(entt::registry& registry, const ir::level& level);

}  // namespace wanderer::sys
