#pragma once

#include <entt/entt.hpp>  // registry, dispatcher, entity
#include <rune/rune.hpp>  // delta_time

#include "wanderer_std.hpp"

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
auto StartBondAnimation(entt::registry& registry, uint32 id) -> entt::entity;

/**
 * \brief Starts a reversed "Bond" animation.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 *
 * \return the created animation entity.
 *
 * \see `StartBondAnimation()`
 */
auto StartReverseOnlyBondAnimation(entt::registry& registry) -> entt::entity;

/**
 * \brief Updates the state of all custom animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param dt the current delta time.
 */
void UpdateCustomAnimations(entt::registry& registry,
                            entt::dispatcher& dispatcher,
                            float dt);

/**
 * \brief Renders all current custom animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void RenderCustomAnimations(const entt::registry& registry);

/// \} End of animation

}  // namespace wanderer::sys
