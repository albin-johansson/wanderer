#pragma once

#include <renderer.hpp>

#include "viewport.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::viewport {

/**
 * Updates the position of the viewport by slowly tracking a movable entity.
 *
 * @pre <code>viewportEntity</code> must have a <code>Viewport</code> component.
 * @pre <code>playerEntity</code> must have a <code>Movable</code> component.
 *
 * @param registry the registry that holds the viewport and the player.
 * @param viewportEntity the entity ID for the viewport.
 * @param movableEntity the entity ID for the movable.
 * @param dt the delta time, in seconds.
 */
void update(entt::registry& registry,
            comp::Viewport::entity viewportEntity,
            entt::entity movableEntity,
            delta dt);

void translate(entt::registry& registry,
               comp::Viewport::entity viewportEntity,
               cen::renderer& renderer);

}  // namespace wanderer::sys::viewport
