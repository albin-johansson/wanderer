#pragma once

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry)
    -> comp::Viewport::entity;

}  // namespace wanderer::sys::viewport
