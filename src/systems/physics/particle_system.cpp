#include "particle_system.hpp"

#include <rune/rune.hpp>  // next_random

#include "components/particle.hpp"
#include "components/viewport.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

constexpr float time_step = 10;     // How much time passes each frame
constexpr float initial_z_pos = 2;  // The initial theoretical Z-coordinate

constexpr float min_initial_x_accel = -20;
constexpr float max_initial_x_accel = 20;

constexpr float min_initial_y_accel = -10;
constexpr float max_initial_y_accel = 10;

constexpr float min_initial_z_accel = 3;
constexpr float max_initial_z_accel = 6;

// Z-acceleration is decremented with this each frame
constexpr float z_accel_decrement = 30;

// These are used to scale the acceleration once a particle has a negative Z-coordinate
constexpr float x_accel = 36;
constexpr float y_accel = 36;
constexpr float z_accel = -30;

void SpawnParticle(entt::registry& registry,
                   const float2 position,
                   const float duration,
                   const cen::color& color)
{
  auto& particle = registry.emplace<Particle>(registry.create());
  particle.position = {position.x, position.y, initial_z_pos};

  particle.acceleration.x = rune::next_random(min_initial_x_accel, max_initial_x_accel);
  particle.acceleration.y = rune::next_random(min_initial_y_accel, max_initial_y_accel);
  particle.acceleration.z = rune::next_random(min_initial_z_accel, max_initial_z_accel);

  particle.now = 0;
  particle.duration = duration;
  particle.color = color;
}

}  // namespace

void SpawnParticles(entt::registry& registry,
                    const float2 origin,
                    const int32 count,
                    const float duration,
                    const cen::color& color)
{
  for (auto i = 0; i < count; ++i) {
    SpawnParticle(registry, origin, duration, color);
  }
}

void UpdateParticles(entt::registry& registry, const float dt)
{
  const auto now = cen::counter::ticks();
  for (auto&& [entity, particle] : registry.view<Particle>().each()) {
    particle.now += time_step * dt;
    if (particle.now >= particle.duration) {
      registry.destroy(entity);
    }
    else {
      particle.position += particle.acceleration * dt;

      if (particle.position.z < 0) {
        particle.position.z = 0;
        particle.acceleration.x *= x_accel * dt;
        particle.acceleration.y *= y_accel * dt;
        particle.acceleration.z *= z_accel * dt;
      }

      particle.acceleration.z -= z_accel_decrement * dt;
    }
  }
}

void RenderParticles(const entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::Viewport>();

  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.GetRenderer();

  for (auto&& [entity, particle] : registry.view<Particle>().each()) {
    const auto rect = cen::rect(particle.position.x,
                                particle.position.y - particle.position.z,
                                2.0f,
                                2.0f);
    if (cen::intersects(viewport.bounds, rect)) {
      renderer.set_color(particle.color);
      renderer.fill_rect_t(rect);
    }
  }
}

}  // namespace wanderer::sys
