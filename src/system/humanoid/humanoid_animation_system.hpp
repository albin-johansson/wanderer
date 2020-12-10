#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer::sys::humanoid {

/**
 * \brief Makes a humanoid enter the idle animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the idle animation.
 */
void enter_idle_animation(entt::registry& registry,
                          entt::entity entity) noexcept;

/**
 * \brief Makes a humanoid enter the movement animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the movement animation.
 * \param dir the dir that the humanoid is facing.
 */
void enter_move_animation(entt::registry& registry,
                          entt::entity entity,
                          direction dir) noexcept;

/**
 * \brief Makes a humanoid enter the melee animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the melee animation.
 */
void enter_melee_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

/**
 * \brief Makes a humanoid enter the spell animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the spell animation.
 */
void enter_spell_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

/**
 * \brief Makes a humanoid enter the bow animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the bow animation.
 */
void enter_bow_animation(entt::registry& registry,
                         entt::entity entity) noexcept;

/**
 * \brief Makes a humanoid enter the spear animation.
 *
 * \note This method has no effect if the supplied entity doesn't
 * have the components `Animated`, `Movable` and `DepthDrawable`.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the spear animation.
 */
void enter_spear_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

/**
 * \brief Updates the state of the animations for all humanoids in the registry.
 *
 * \param registry the registry that holds the humanoids that will be updated.
 */
void update_animation(entt::registry& registry);

}  // namespace wanderer::sys::humanoid
