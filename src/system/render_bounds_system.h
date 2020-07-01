#pragma once

#include "render_bounds.h"
#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system {

[[nodiscard]] auto calculate_render_bounds(
    entt::registry& registry,
    component::Viewport::entity viewportEntity,
    int rows,
    int cols) -> component::RenderBounds;

}  // namespace wanderer::system
