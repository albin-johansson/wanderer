#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::sys {

void load_objects(entt::registry& registry,
                  graphics_context& graphics,
                  const ir::level& level);

}  // namespace wanderer::sys
