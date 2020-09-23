#pragma once

#include "component/viewport.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry)
    -> comp::viewport::entity;

}  // namespace wanderer::sys::viewport
