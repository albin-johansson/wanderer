#pragma once

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup tile-system Tile system
 *
 * \brief Handles aspects related to tilemap tiles.
 */

/// \addtogroup tile-system
/// \{

/**
 * \brief Renders all tile layers.
 *
 * \details This function iterates all tile layers in a registry and renders all visible
 * tiles according to the predetermined render bounds.
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 */
void render_tiles(const entt::registry& registry, graphics_ctx& graphics);

/// \} End of group tile-system

}  // namespace wanderer::sys
