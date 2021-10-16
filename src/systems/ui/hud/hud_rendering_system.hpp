#pragma once

#include <centurion.hpp>  // ipoint
#include <entt.hpp>       // registry

namespace wanderer::sys {

/// \name HUD
/// \{

/**
 * \brief Renders the game HUD.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param mousePos the current position of the mouse.
 */
void render_hud(const entt::registry& shared,
                cen::ipoint mousePos);

/// \} End of HUD

}  // namespace wanderer::sys
