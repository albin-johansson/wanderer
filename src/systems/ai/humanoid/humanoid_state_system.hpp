#pragma once

#include <entt.hpp>  // registry, dispatcher, entity

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Makes a humanoid entity enter its idle state.
 *
 * \details This function will stop the movement of the humanoid, along with updating its
 * animation.
 *
 * \pre The entity must be a humanoid.
 * \pre The entity cannot already be idle.
 *
 * \param registry the current level registry.
 * \param entity the humanoid entity that will become idle.
 */
void make_humanoid_idle(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid entity enter its movement state.
 *
 * \details This function will also update the animation of the humanoid.
 *
 * \pre The entity must be a humanoid.
 * \pre The entity cannot already be in the movement state.
 *
 * \param registry the current level registry.
 * \param entity the humanoid entity that will enter its movement state.
 */
void make_humanoid_move(entt::registry& registry, entt::entity entity);

/**
 * \brief Updates the state of all humanoids.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the dispatcher that will be used.
 */
void update_humanoid_states(entt::registry& registry, entt::dispatcher& dispatcher);

/// \} End of humanoid

}  // namespace wanderer::sys
