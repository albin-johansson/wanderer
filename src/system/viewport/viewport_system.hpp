#pragma once

#include <centurion.hpp>

#include "delta.hpp"
#include "level.hpp"
#include "vector2.hpp"
#include "viewport.hpp"

namespace wanderer::sys {

void center_viewport_on(entt::registry& registry,
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
void update_viewport(level& level,
                     const entt::entity movableEntity,
                     const delta_t dt);

void translate_renderer_viewport(const entt::registry& registry,
                                 comp::viewport::entity viewportEntity,
                                 cen::renderer& renderer);

}  // namespace wanderer::sys
