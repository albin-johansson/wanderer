#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry, dispatcher
#include <rune.hpp>       // delta_time

#include "core/aliases/map_id.hpp"
#include "events/level_fade_events_event.hpp"

namespace wanderer::sys {

/// \name UI
/// \{

/**
 * \brief Begins a level switch animation.
 *
 * \ingroup systems
 *
 * \param registry the registry associated with the current level.
 * \param map the ID of the target map.
 *
 * \since 0.1.0
 */
void start_level_change_animation(entt::registry& registry, map_id map);

/// \} End of UI

}  // namespace wanderer::sys
