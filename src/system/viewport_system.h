#pragma once

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer::system::viewport {

/**
 * Updates the position of the viewport by slowly tracking a movable entity.
 *
 * @pre <code>viewportEntity</code> must have a <code>Viewport</code> component.
 * @pre <code>playerEntity</code> must have a <code>Movable</code> component.
 *
 * @param registry the registry that holds the viewport and the player.
 * @param viewportEntity the entity ID for the viewport.
 * @param movableEntity the entity ID for the movable.
 * @param delta the delta time, in seconds.
 */
void update(entt::registry& registry,
            Viewport::entity viewportEntity,
            entt::entity movableEntity,
            Delta delta);

}  // namespace wanderer::system::viewport
