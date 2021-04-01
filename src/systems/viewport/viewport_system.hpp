#pragma once

#include <centurion.hpp>  // renderer, farea
#include <entt.hpp>       // registry

#include "delta.hpp"
#include "level.hpp"
#include "vector2.hpp"
#include "viewport.hpp"

namespace wanderer::sys {

[[nodiscard]] auto make_viewport(const cen::farea& levelSize) noexcept -> ctx::viewport;

void center_viewport_on(entt::registry& registry, const float2& position);

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
void update_viewport(level& level, const entt::entity movableEntity, const delta_t dt);

void translate_viewport(const entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys
