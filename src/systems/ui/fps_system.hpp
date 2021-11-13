#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer::sys {

/// \name UI
/// \{

/**
 * \brief Updates the FPS data.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param dt the current delta time.
 */
void UpdateFps(entt::registry& shared, float dt);

/**
 * \brief Renders the current FPS and frame duration.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 */
void RenderFps(const entt::registry& shared);

/// \} End of UI

}  // namespace wanderer::sys
