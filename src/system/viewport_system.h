#pragma once

#include <area.h>

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::viewport {

void update(entt::registry& registry,
            ViewportEntity viewportEntity,
            entt::entity playerEntity,
            Delta delta);

}  // namespace wanderer::system::viewport
