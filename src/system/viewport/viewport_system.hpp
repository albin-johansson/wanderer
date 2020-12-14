#pragma once

#include <cen/renderer.hpp>

#include "delta.hpp"
#include "level.hpp"
#include "vector2.hpp"
#include "viewport.hpp"

namespace wanderer::sys::viewport {

void center_on(entt::registry& registry,
               comp::viewport::entity viewportEntity,
               const vector2f& position);

/**
 * \brief Updates the position of the viewport by slowly tracking a movable
 * entity.
 *
 * \pre `playerEntity` must have a `Movable` component.
 *
 * \param level the level associated with the viewport that will be updated.
 * \param movableEntity the entity ID for the movable.
 * \param dt the delta time, in seconds.
 */
void update(level& level, entt::entity movableEntity, delta_t dt);

void translate(const entt::registry& registry,
               comp::viewport::entity viewportEntity,
               cen::renderer& renderer);

}  // namespace wanderer::sys::viewport
