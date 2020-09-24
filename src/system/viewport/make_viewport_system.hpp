#pragma once

#include <entt.hpp>

#include "component/viewport.hpp"

namespace wanderer::sys::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry)
    -> comp::viewport::entity;

}  // namespace wanderer::sys::viewport
