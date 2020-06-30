#pragma once

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry) -> Viewport::entity;

}  // namespace wanderer::system::viewport
