#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup cinematic-system Cinematic system
 *
 * \brief Manages blocking cinematic transitions intended to display basic information.
 *
 * \todo Allow scheduling multiple consecutive cinematics.
 */

/// \addtogroup cinematic-system
/// \{

/**
 * \brief Schedules the "Wanderer" title cinematic fade, intended to shown at startup.
 *
 * \param registry the source registry.
 */
void schedule_startup_cinematic_fade(entt::registry& registry);

/**
 * \brief Updates the state of the current cinematic fade, if there is one.
 *
 * \param registry the source registry.
 */
void update_cinematic_fade(entt::registry& registry);

/**
 * \brief Renders any current cinematic fade, if there is one.
 *
 * \param registry the source registry.
 * \param graphics the current graphics context.
 */
void render_cinematic_fade(const entt::registry& registry, Graphics& graphics);

/**
 * \brief Indicates whether there is an active cinematic transition.
 *
 * \param registry the source registry.
 *
 * \return `true` if a cinematic fade is active; `false` otherwise.
 */
[[nodiscard]] auto is_cinematic_fade_active(const entt::registry& registry) -> bool;

/// \} End of group cinematic-system

}  // namespace wanderer::sys
