#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup animation-system
 *
 * \brief Manages animation aspects.
 */

/// \addtogroup animation-system
/// \{

/**
 * \brief Updates the state of all animations.
 *
 * \param registry the current level registry.
 */
void update_animations(entt::registry& registry);

/**
 * \brief Makes a humanoid enter its idle animation.
 *
 * \param registry a level registry.
 * \param humanoidEntity the associated humanoid entity.
 * \param directionMask the current direction mask of the humanoid.
 */
void enter_humanoid_idle_animation(entt::registry& registry,
                                   entt::entity humanoidEntity,
                                   uint32 directionMask);

/**
 * \brief Makes a humanoid enter its walk animation.
 *
 * \param registry a level registry.
 * \param humanoidEntity the associated humanoid entity.
 * \param directionMask the current direction mask of the humanoid.
 */
void enter_humanoid_walk_animation(entt::registry& registry,
                                   entt::entity humanoidEntity,
                                   uint32 directionMask);

/// \} End of group animation-system

}  // namespace wanderer::sys