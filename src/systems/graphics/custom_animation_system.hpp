#pragma once

#include <entt.hpp>             // registry, dispatcher, entity
#include <rune/everything.hpp>  // delta_time

#include "core/aliases/ints.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Animation
/// \{

/**
 * \brief Starts a "Bond" animation, i.e. and animation that consists of a shrinking
 * centered "rectangle".
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param id the ID that will be associated with the animation.
 *
 * \return the created animation entity.
 */
auto start_bond_animation(entt::registry& registry, uint32 id) -> entt::entity;

/**
 * \brief Starts a reversed "Bond" animation.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 *
 * \return the created animation entity.
 *
 * \see `start_bond_animation()`
 */
auto start_reverse_only_bond_animation(entt::registry& registry) -> entt::entity;

/**
 * \brief Updates the state of all custom animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param dt the current delta time.
 */
void update_custom_animations(entt::registry& registry,
                              entt::dispatcher& dispatcher,
                              float dt);

/**
 * \brief Renders all current custom animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 */
void render_custom_animations(const entt::registry& registry, graphics_context& graphics);

/// \} End of animation

}  // namespace wanderer::sys
