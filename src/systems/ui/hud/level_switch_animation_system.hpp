#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry, dispatcher

#include "core/aliases/delta_time.hpp"
#include "core/aliases/map_id.hpp"
#include "events/level_fade_events_event.hpp"

namespace wanderer::sys {

/**
 * \brief Updates the state of a level switch animations, although there should
 * only ever be one active at a time.
 *
 * \param registry the registry associated with the current level.
 * \param dispatcher the event dispatcher that will be used.
 * \param dt the current delta time.
 *
 * \since 0.1.0
 */
void update_level_switch_animations(entt::registry& registry,
                                    entt::dispatcher& dispatcher,
                                    delta_time dt);

/**
 * \brief Renders all level switch animations, although there should only
 * ever be one active at a time.
 *
 * \param registry the registry associated with the current level.
 * \param renderer the renderer that will be used.
 *
 * \since 0.1.0
 */
void render_level_switch_animations(const entt::registry& registry,
                                    cen::renderer& renderer);

/**
 * \brief Begins a level switch animation.
 *
 * \param registry the registry associated with the current level.
 * \param map the ID of the target map.
 *
 * \since 0.1.0
 */
void start_level_fade_animation(entt::registry& registry, map_id map);

/**
 * \brief "Ends" a level switch animation by running an animation backwards.
 *
 * \note The registry that is supplied to this function should not be the
 * same as the registry supplied to `start_level_fade_animation()`, before
 * calling this function.
 *
 * \param registry the registry associated with the current level.
 * \param event the event that contains information about the animation.
 *
 * \since 0.1.0
 */
void end_level_fade_animation(entt::registry& registry,
                              const event::level_faded_in& event);

}  // namespace wanderer::sys
