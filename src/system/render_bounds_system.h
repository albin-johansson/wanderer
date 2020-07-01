#pragma once

#include "render_bounds.h"
#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys {

[[nodiscard]] auto calculate_render_bounds(
    entt::registry& registry,
    comp::Viewport::entity viewportEntity,
    int rows,
    int cols) -> comp::RenderBounds;

}  // namespace wanderer::sys
