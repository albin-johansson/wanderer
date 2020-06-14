#pragma once

#include <renderer.h>

#include "types.h"

namespace wanderer::system {

void update_translation_viewport(entt::registry& registry,
                                 entt::entity viewport,
                                 centurion::Renderer& renderer);

}  // namespace wanderer::system
