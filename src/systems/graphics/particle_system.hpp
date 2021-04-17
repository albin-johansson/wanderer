#pragma once

#include <centurion.hpp>  // renderer, color
#include <entt.hpp>       // registry

#include "core/aliases/delta_time.hpp"
#include "core/aliases/float2.hpp"

namespace wanderer::sys {

/// \name Particles
/// \{

void spawn_particles(entt::registry& registry,
                     float2 origin,
                     int count,
                     float duration,
                     const cen::color& color);

void add_particle(entt::registry& registry,
                  float2 position,
                  float duration,
                  const cen::color& color);

void update_particles(entt::registry& registry, delta_time dt);

void render_particles(const entt::registry& registry, cen::renderer& renderer);

/// } End of particles

}  // namespace wanderer::sys
