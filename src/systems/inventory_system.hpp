#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry

#include "player.hpp"

namespace wanderer::sys {

void update_inventory_triggers(entt::registry& registry, comp::player::entity player);

void render_inventory(const entt::registry& registry,
                      cen::renderer& renderer,
                      const cen::ipoint& mousePos);

}  // namespace wanderer::sys
