#pragma once

#include <centurion.hpp>        // renderer
#include <entt.hpp>             // registry, dispatcher
#include <rune/everything.hpp>  // delta_time

#include "common/map_id.hpp"

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
void StartLevelChangeAnimation(entt::registry& registry, map_id map);

/// \} End of UI

}  // namespace wanderer::sys
