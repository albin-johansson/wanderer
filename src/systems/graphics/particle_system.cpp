#include "particle_system.hpp"

#include "components/graphics/particle.hpp"
#include "core/math/get_random.hpp"

namespace wanderer::sys {

inline constexpr float time_step = 10;     // How much time passes each frame
inline constexpr float initial_z_pos = 2;  // The initial theoretical Z-coordinate

inline constexpr float min_initial_x_accel = -20;
inline constexpr float max_initial_x_accel = 20;

inline constexpr float min_initial_y_accel = -10;
inline constexpr float max_initial_y_accel = 10;

inline constexpr float min_initial_z_accel = 3;
inline constexpr float max_initial_z_accel = 6;

// Z-acceleration is decremented with this each frame
inline constexpr float z_accel_decrement = 30;

// These are used to scale the acceleration once a particle has a negative Z-coordinate
inline constexpr float x_accel = 36;
inline constexpr float y_accel = 36;
inline constexpr float z_accel = -30;

void spawn_particles(entt::registry& registry,
                     const float2 origin,
                     const int count,
                     const float duration,
                     const cen::color& color)
{
  for (auto i = 0; i < count; ++i)
  {
    add_particle(registry, origin, duration, color);
  }
}

void add_particle(entt::registry& registry,
                  const float2 position,
                  const float duration,
                  const cen::color& color)
{
  auto& particle = registry.emplace<comp::particle>(registry.create());
  particle.position = {position.x, position.y, initial_z_pos};

  particle.acceleration.x = get_random(min_initial_x_accel, max_initial_x_accel);
  particle.acceleration.y = get_random(min_initial_y_accel, max_initial_y_accel);
  particle.acceleration.z = get_random(min_initial_z_accel, max_initial_z_accel);

  particle.now = 0;
  particle.duration = duration;
  particle.color = color;
}

void update_particles(entt::registry& registry, const delta_time dt)
{
  const auto now = cen::counter::ticks();
  for (auto&& [entity, particle] : registry.view<comp::particle>().each())
  {
    particle.now += time_step * dt;
    if (particle.now >= particle.duration)
    {
      registry.destroy(entity);
    }
    else
    {
      particle.position += particle.acceleration * dt;

      if (particle.position.z < 0)
      {
        particle.position.z = 0;
        particle.acceleration.x *= x_accel * dt;
        particle.acceleration.y *= y_accel * dt;
        particle.acceleration.z *= z_accel * dt;
      }

      particle.acceleration.z -= z_accel_decrement * dt;
    }
  }
}

void render_particles(const entt::registry& registry, cen::renderer& renderer)
{
  for (auto&& [entity, particle] : registry.view<const comp::particle>().each())
  {
    const auto rect = cen::rect(particle.position.x,
                                particle.position.y - particle.position.z,
                                2.0f,
                                2.0f);
    renderer.set_color(particle.color);
    renderer.fill_rect_t(rect);
  }
}

}  // namespace wanderer::sys
