#pragma once

#include <entt.hpp>  // registry

#include "components/level.hpp"
#include "core/aliases/map_id.hpp"
#include "events/custom_animation_halfway_event.hpp"

namespace wanderer::sys {

/// \name Levels
/// \{

/**
 * \brief Prepares the current level before another level is enabled.
 *
 * \pre The event message must be `glob::switch_level_id`.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param event the animation event associated with the level switch.
 *
 * \return the ID associated with the next level.
 */
[[nodiscard]] auto prepare_current_level_before_switch(
    entt::registry& shared,
    const custom_animation_halfway_event& event) -> map_id;

/**
 * \brief Enables the level associated with the specified ID.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param id the ID associated with the level that will be enabled.
 */
void enable_level(entt::registry& shared, map_id id);

/**
 * \brief Returns the currently active level.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return the currently active level.
 */
[[nodiscard]] auto current_level(entt::registry& shared) -> comp::level&;

/// \copydoc current_level()
[[nodiscard]] auto current_level(const entt::registry& shared) -> const comp::level&;

/**
 * \brief Indicates whether or not the active level is an outside level.
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return `true` if the currently active level is outside; `false` otherwise.
 */
[[nodiscard]] auto is_current_level_outside(const entt::registry& shared) -> bool;

/// \} End of levels

}  // namespace wanderer::sys
