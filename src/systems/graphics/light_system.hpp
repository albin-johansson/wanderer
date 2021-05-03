#pragma once

#include <entt.hpp>  // registry

#include "components/ctx/settings.hpp"
#include "components/ctx/time_of_day.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Lights
/// \{

/**
 * \brief Updates the fluctuations of all lights.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void update_lights(entt::registry& registry);

/**
 * \brief Updates the position of the light attached to the player entity.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void update_player_light_position(entt::registry& registry);

/**
 * \brief Renders all lights currently in the viewport bounds.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 * \param time the current time state.
 * \param settings the current settings.
 */
void render_lights(const entt::registry& registry,
                   graphics_context& graphics,
                   const ctx::time_of_day& time,
                   const ctx::settings& settings);

/// \} End of lights

}  // namespace wanderer::sys
