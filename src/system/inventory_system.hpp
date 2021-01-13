#pragma once

#include <cen/renderer.hpp>  // renderer
#include <entt.hpp>          // registry

#include "player.hpp"

namespace wanderer::sys::inventory {

void update_triggers(entt::registry& registry, comp::player::entity player);

void render(const entt::registry& registry,
            cen::renderer& renderer,
            const cen::ipoint& mousePos);

}  // namespace wanderer::sys::inventory
