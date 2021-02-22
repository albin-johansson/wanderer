#pragma once

#include <entt.hpp>

#include "parse_ir.hpp"

namespace wanderer {

void add_objects(entt::registry& registry, const ir::level& level);

}  // namespace wanderer
