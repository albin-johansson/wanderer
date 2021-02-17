#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

#include "delta.hpp"
#include "vector2.hpp"

namespace wanderer::sys {

void add_particle(entt::registry& registry, const vector2f& position);

void update_particles(entt::registry& registry, delta_t dt);

void render_particles(const entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys
