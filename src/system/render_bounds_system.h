#pragma once

#include "render_bounds.h"
#include "wanderer_stdinc.h"

namespace wanderer::system {

[[nodiscard]] RenderBounds calculate_render_bounds(entt::registry& registry,
                                                   entt::entity viewportEntity,
                                                   int rows,
                                                   int cols);

}  // namespace wanderer::system
