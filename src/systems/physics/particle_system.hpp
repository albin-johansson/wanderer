#pragma once

#include <centurion.hpp>  // color
#include <entt.hpp>       // registry

#include "common/float2.hpp"

namespace wanderer::sys {

/// \name Particles
/// \{

/**
 * \brief Spawns a group of particles in the current level.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param origin the origin spawn position position of the particles.
 * \param count the number of particles that will be spawned.
 * \param duration the time that the particles will exist, before disappearing. Note, this
 * has no unit.
 * \param color the color of the particles.
 */
void SpawnParticles(entt::registry& registry,
                    float2 origin,
                    int count,
                    float duration,
                    const cen::color& color);

/**
 * \brief Updates all particles in the current level.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dt the current delta time.
 */
void UpdateParticles(entt::registry& registry, float dt);

/**
 * \brief Renders all particles within the current viewport.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void RenderParticles(const entt::registry& registry);

/// } End of particles

}  // namespace wanderer::sys
