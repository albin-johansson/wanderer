#pragma once

#include <entt.hpp>

#include "graphics_context.hpp"
#include "parse_ir.hpp"

namespace wanderer {

void add_objects(entt::registry& registry,
                 const graphics_context& graphics,
                 const ir::level& level);

}  // namespace wanderer
