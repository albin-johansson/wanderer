#pragma once

#include <renderer.h>

#include "types.h"

namespace wanderer {

void update_translation_viewport(entt::registry& registry,
                                 entt::entity viewport,
                                 centurion::Renderer& renderer);

}
