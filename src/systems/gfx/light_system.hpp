#pragma once

#include <entt.hpp>  // registry

#include "components/settings.hpp"
#include "components/time_of_day.hpp"

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
void UpdateLights(entt::registry& registry);

/**
 * \brief Updates the position of the light attached to the player entity.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void UpdatePlayerLightPosition(entt::registry& registry);

/**
 * \brief Renders all lights currently in the viewport bounds.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param time the current time state.
 */
void RenderLights(const entt::registry& registry, const ctx::TimeOfDay& time);

/// \} End of lights

}  // namespace wanderer::sys
