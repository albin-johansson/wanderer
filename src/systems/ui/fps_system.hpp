#pragma once

#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

#include "core/graphics/graphics_context.hpp"

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
void update_fps(entt::registry& shared, float dt);

/**
 * \brief Renders the current FPS and frame duration.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param graphics the graphics context that will be used.
 */
void render_fps(const entt::registry& shared, graphics_context& graphics);

/// \} End of UI

}  // namespace wanderer::sys
