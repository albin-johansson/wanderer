#pragma once

#include <entt/entt.hpp>  // registry

#include "components/level.hpp"
#include "events/custom_animation_halfway_event.hpp"
#include "wanderer_std.hpp"

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
[[nodiscard]] auto PrepareCurrentLevelBeforeSwitch(
    entt::registry& shared,
    const CustomAnimationHalfwayEvent& event) -> MapID;

/**
 * \brief Enables the level associated with the specified ID.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param id the ID associated with the level that will be enabled.
 */
void EnableLevel(entt::registry& shared, MapID id);

/**
 * \brief Returns the currently active level.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return the currently active level.
 */
[[nodiscard]] auto CurrentLevel(entt::registry& shared) -> Level&;

/// \copydoc CurrentLevel()
[[nodiscard]] auto CurrentLevel(const entt::registry& shared) -> const Level&;

/**
 * \brief Indicates whether or not the active level is an outside level.
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return `true` if the currently active level is outside; `false` otherwise.
 */
[[nodiscard]] auto IsCurrentLevelOutside(const entt::registry& shared) -> bool;

/// \} End of levels

}  // namespace wanderer::sys
