#pragma once

#include <renderer.h>

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system {

void update_translation_viewport(entt::registry& registry,
                                 Viewport::entity viewportEntity,
                                 ctn::Renderer& renderer);

}  // namespace wanderer::system
