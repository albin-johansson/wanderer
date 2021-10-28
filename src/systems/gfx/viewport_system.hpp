#pragma once

#include <centurion.hpp>  // farea
#include <entt.hpp>       // registry

#include "components/viewport.hpp"
#include "wanderer_std.hpp"

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
[[nodiscard]] auto MakeViewport(cen::farea levelSize) noexcept -> ctx::Viewport;

/**
 * \brief Centers the viewport on the specified position.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param position the world position to center the viewport on.
 */
void CenterViewportOn(entt::registry& registry, float2 position);

/**
 * \brief Updates the position of the viewport by slowly tracking a movable entity.
 *
 * \pre `target` must feature a `movable` component.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param target the movable entity that will be tracked.
 * \param dt the current delta time.
 */
void UpdateViewport(entt::registry& registry, entt::entity target, float dt);

/**
 * \brief Updates the translation viewport of a renderer based on the current viewport.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void TranslateViewport(const entt::registry& registry);

/// \} End of viewport

}  // namespace wanderer::sys
