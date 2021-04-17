#pragma once

#include <centurion.hpp>  // renderer, farea
#include <entt.hpp>       // registry

#include "components/ctx/viewport.hpp"
#include "core/aliases/delta_time.hpp"
#include "core/aliases/float2.hpp"
#include "core/levels/level.hpp"

namespace wanderer::sys {

/// \name Viewport
/// \{

[[nodiscard]] auto make_viewport(cen::farea levelSize) noexcept -> ctx::viewport;

void center_viewport_on(entt::registry& registry, float2 position);

/**
 * \brief Updates the position of the viewport by slowly tracking a movable
 * entity.
 *
 * \pre `movableEntity` must have a `movable` component.
 *
 * \param level the level associated with the viewport that will be updated.
 * \param movableEntity the entity ID for the movable.
 * \param dt the delta time, in seconds.
 */
void update_viewport(level& level, entt::entity movableEntity, delta_time dt);

void translate_viewport(const entt::registry& registry, cen::renderer& renderer);

/// \} End of viewport

}  // namespace wanderer::sys
