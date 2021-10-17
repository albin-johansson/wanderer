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
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the idle animation.
 */
void EnterIdleAnimation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter its movement animation.
 *
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the movement animation.
 * \param dir the direction that the humanoid is facing.
 */
void EnterMoveAnimation(entt::registry& registry, entt::entity entity, Direction dir);

/**
 * \brief Makes a humanoid enter the melee animation.
 *
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the melee animation.
 */
void EnterMeleeAnimation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter the spell animation.
 *
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the spell animation.
 */
void EnterSpellAnimation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter the bow animation.
 *
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the bow animation.
 */
void EnterBowAnimation(entt::registry& registry, entt::entity entity);

/**
 * \brief Makes a humanoid enter its spear animation.
 *
 * \pre `entity` must have `comp::Animation`, `comp::Movable` and `comp::Drawable`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the spear animation.
 */
void EnterSpearAnimation(entt::registry& registry, entt::entity entity);

/**
 * \brief Updates all humanoids animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void UpdateHumanoidAnimations(entt::registry& registry);

/// \} End of humanoids

}  // namespace wanderer::sys
