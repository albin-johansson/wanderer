#pragma once

#include <entt.hpp>  // registry

#include "components/player.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Inventory
/// \{

void RenderInventoryBar(const entt::registry& registry, GraphicsContext& graphics);

void RenderInventory(const entt::registry& registry,
                     GraphicsContext& graphics,
                     const cen::ipoint& mousePos);

/// \} End of inventory

}  // namespace wanderer::sys
