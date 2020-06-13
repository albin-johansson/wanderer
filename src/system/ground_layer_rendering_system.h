#pragma once

#include <renderer.h>

#include "types.h"

namespace wanderer {

void render_ground_layers(entt::registry& registry,
                          entt::entity mapEntity,
                          entt::entity viewportEntity,
                          centurion::Renderer& renderer);

}
