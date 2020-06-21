#pragma once

#include "render_bounds.h"
#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system {

[[nodiscard]] RenderBounds calculate_render_bounds(
    entt::registry& registry,
    ViewportEntity viewportEntity,
    int rows,
    int cols);

}  // namespace wanderer::system
