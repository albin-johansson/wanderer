#pragma once

#include <renderer.h>

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::viewport {

void translate(entt::registry& registry,
               Viewport::entity viewportEntity,
               ctn::Renderer& renderer);

}  // namespace wanderer::system::viewport
