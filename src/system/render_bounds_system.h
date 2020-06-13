#pragma once

#include "render_bounds.h"
#include "types.h"

namespace wanderer {

RenderBounds calculate_render_bounds(entt::registry& registry,
                                     entt::entity viewportEntity,
                                     int rows,
                                     int cols);

}
