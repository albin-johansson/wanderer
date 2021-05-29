#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry

#include "components/player.hpp"

namespace wanderer::sys {

/// \name Inventory
/// \{

void render_inventory(const entt::registry& registry,
                      cen::renderer& renderer,
                      const cen::ipoint& mousePos);

/// \} End of inventory

}  // namespace wanderer::sys
