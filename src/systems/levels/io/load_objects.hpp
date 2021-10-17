#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

void LoadObjects(entt::registry& registry,
                 GraphicsContext& graphics,
                 const ir::level& level);

}  // namespace wanderer::sys
