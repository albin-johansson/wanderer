#pragma once

#include <centurion.hpp>  // ipoint
#include <entt.hpp>       // registry

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
 * \param mousePos the current position of the mouse.
 */
void render_hud(const entt::registry& shared,
                graphics_context& graphics,
                cen::ipoint mousePos);

/// \} End of HUD

}  // namespace wanderer::sys
