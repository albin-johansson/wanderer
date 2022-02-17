#pragma once

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \brief Renders all tile layers.
 *
 * \details This function assumes that the render bounds has been calculated beforehand.
 *
 * \param registry the current level registry.
 * \param cfg the game configuration.
 * \param graphics the graphics context that will be used.
 */
void render_tiles(const entt::registry& registry,
                  const game_cfg& cfg,
                  graphics_ctx& graphics);

}  // namespace wanderer::sys
