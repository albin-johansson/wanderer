#pragma once

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup tile-system Tile system
 *
 * \brief Handles aspects related to tilemap tiles and tile objects.
 */

/// \addtogroup tile-system
/// \{

/**
 * \brief Clears the frame-by-frame cache for the effective appearance of tiles.
 *
 * \param registry the level registry.
 */
void clear_effective_appearance_tile_cache(entt::registry& registry);

/**
 * \brief Updates the state of tile objects, such as syncing their effective appearance.
 *
 * \param registry the level registry.
 */
void update_tile_objects(entt::registry& registry);

/**
 * \brief Renders all tile layers.
 *
 * \details This function iterates all tile layers in a registry and renders all
 * visible tiles according to the predetermined render bounds.
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 */
void render_tiles(const entt::registry& registry, graphics_ctx& graphics);

/// \} End of group tile-system

}  // namespace wanderer::sys
