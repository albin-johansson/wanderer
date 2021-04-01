#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "viewport.hpp"

namespace wanderer::sys {

[[nodiscard]] auto make_viewport(entt::registry& registry, const cen::farea& levelSize)
    -> comp::viewport::entity;

}  // namespace wanderer::sys
