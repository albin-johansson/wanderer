#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer {

/**
 * \brief Loads the initial levels into the shared data registry.
 *
 * \details This function should be called once at the startup of the game. Other
 * functions are then used to load save files upon request.
 *
 * \ingroup core
 *
 * \param[in,out] shared the shared data registry that will store the loaded levels.
 * \param graphics the graphics context used when loading textures.
 *
 * \see `sys::make_level()`
 */
void load_levels(entt::registry& shared, graphics_context& graphics);

}  // namespace wanderer
