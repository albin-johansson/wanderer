#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name HUD
/// \{

/**
 * \brief Renders the game HUD.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param graphics the graphics context that will be used.
 */
void render_hud(const entt::registry& shared, graphics_context& graphics);

/// \} End of HUD

}  // namespace wanderer::sys
