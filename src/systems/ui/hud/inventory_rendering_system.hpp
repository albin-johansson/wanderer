#pragma once

#include <entt.hpp>       // registry

#include "core/graphics/graphics_context.hpp"
#include "components/player.hpp"

namespace wanderer::sys {

/// \name Inventory
/// \{

void render_inventory_bar(const entt::registry& registry,
                          graphics_context& graphics);

void render_inventory(const entt::registry& registry,
                      graphics_context& graphics,
                      const cen::ipoint& mousePos);

/// \} End of inventory

}  // namespace wanderer::sys
