#pragma once

#include <cen/area.hpp>
#include <entt.hpp>

#include "viewport.hpp"

namespace wanderer::sys::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry,
                                 const cen::farea& levelSize)
    -> comp::viewport::entity;

}  // namespace wanderer::sys::viewport
