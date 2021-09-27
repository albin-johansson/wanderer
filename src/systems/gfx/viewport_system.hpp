#pragma once

#include <centurion.hpp>        // renderer, farea
#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

#include "common/float2.hpp"
#include "components/ctx/viewport.hpp"
#include "components/physics/movable.hpp"

namespace wanderer::sys {

/// \name Viewport
/// \{

/**
 * \brief Creates and returns a viewport.
 *
 * \ingroup systems
 *
 * \param levelSize the size of the level that the viewport will be used in.
 *
 * \return the created viewport.
 */
[[nodiscard]] auto make_viewport(cen::farea levelSize) noexcept -> ctx::viewport;

/**
 * \brief Centers the viewport on the specified position.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param position the world position to center the viewport on.
 */
void center_viewport_on(entt::registry& registry, float2 position);

/**
 * \brief Updates the position of the viewport by slowly tracking a movable entity.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param target the movable entity that will be tracked.
 * \param dt the current delta time.
 */
void update_viewport(entt::registry& registry, comp::movable::entity target, float dt);

/**
 * \brief Updates the translation viewport of a renderer based on the current viewport.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param renderer the renderer which will have its translation viewport updated.
 */
void translate_viewport(const entt::registry& registry, cen::renderer& renderer);

/// \} End of viewport

}  // namespace wanderer::sys
