#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \brief Updates the tilemap render bounds for a level registry.
 *
 * \param registry the current level registry.
 * \param cfg the game configuration.
 */
void update_render_bounds(entt::registry& registry, const game_cfg& cfg);

/**
 * \brief Updates the viewport state.
 *
 * \param registry the current level registry.
 * \param dt the current delta time.
 */
void update_viewport(entt::registry& registry, float32 dt);

}  // namespace wanderer::sys