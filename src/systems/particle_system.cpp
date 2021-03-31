#include "particle_system.hpp"

#include <centurion.hpp>

#include "get_random.hpp"
#include "particle.hpp"

namespace wanderer::sys {

void add_particle(entt::registry& registry,
                  const float2& position,
                  const cen::color& color,
                  const int nTicks)
{
  using namespace cen::literals;

  auto& particle = registry.emplace<comp::particle>(registry.create());
  particle.position = {position.x, position.y, 2};

  particle.acceleration.x = get_random(-12.0f, 12.0f);
  particle.acceleration.y = get_random(-8.0f, 8.0f);
  particle.acceleration.z = get_random(0.0f, 3.5f) + 2.0f;

  particle.tick = 0;
  particle.nTicks = nTicks;
  particle.color = color;
}

void update_particles(entt::registry& registry, const delta_t dt)
{
  const auto now = cen::counter::ticks();

  const auto view = registry.view<comp::particle>();
  view.each([&](const entt::entity entity, comp::particle& particle) {
    ++particle.tick;
    if (particle.tick >= particle.nTicks)
    {
      registry.destroy(entity);
    }
    else
    {
      particle.position += particle.acceleration * dt;

      if (particle.position.z < 0)
      {
        particle.position.z = 0;
        particle.acceleration.x *= 0.6f;
        particle.acceleration.y *= 0.6f;
        particle.acceleration.z *= -0.5f;
      }

      particle.acceleration.z -= 0.15f;
    }
  });
}

void render_particles(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::particle>();
  view.each([&](const comp::particle& particle) {
    const cen::frect rect{
        {particle.position.x, particle.position.y - particle.position.z},
        {2.0f, 2.0f}};
    renderer.set_color(particle.color);
    renderer.fill_rect_t(rect);
  });
}

}  // namespace wanderer::sys
