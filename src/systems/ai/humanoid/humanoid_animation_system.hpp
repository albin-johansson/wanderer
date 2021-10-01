#pragma once

#include <entt.hpp>  // registry, entity

#include "core/direction.hpp"

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Makes a humanoid enter its idle animation.
 *
 * \ingroup systems
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the idle animation.
 */
void enter_idle_animation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter its movement animation.
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the movement animation.
 * \param dir the direction that the humanoid is facing.
 */
void enter_move_animation(entt::registry& registry, entt::entity entity, direction dir);

/**
 * \brief Makes a humanoid enter the melee animation.
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the melee animation.
 */
void enter_melee_animation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter the spell animation.
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the spell animation.
 */
void enter_spell_animation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter the bow animation.
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the bow animation.
 */
void enter_bow_animation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter its spear animation.
 *
 * \pre `entity` must have `comp::animation`, `comp::movable` and `comp::drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the spear animation.
 */
void enter_spear_animation(entt::registry& registry, entt::entity entity);

/**
 * \brief Updates all humanoids animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void update_humanoid_animations(entt::registry& registry);

/// \} End of humanoids

}  // namespace wanderer::sys
