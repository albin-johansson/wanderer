#pragma once

#include <cen/renderer.hpp>

#include "component/viewport.hpp"
#include "delta.hpp"

namespace wanderer::sys::viewport {

/**
 * Updates the position of the viewport by slowly tracking a movable entity.
 *
 * @pre `viewportEntity` must have a `Viewport` component.
 * @pre `playerEntity` must have a `Movable` component.
 *
 * @param registry the registry that holds the viewport and the player.
 * @param viewportEntity the entity ID for the viewport.
 * @param movableEntity the entity ID for the movable.
 * @param dt the delta time, in seconds.
 */
void update(entt::registry& registry,
            comp::viewport::entity viewportEntity,
            entt::entity movableEntity,
            delta dt);

void translate(entt::registry& registry,
               comp::viewport::entity viewportEntity,
               cen::renderer& renderer);

}  // namespace wanderer::sys::viewport
