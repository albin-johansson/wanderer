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
  particle.x = position.x;
  particle.y = position.y;
  particle.z = 2;

  particle.dx = get_random(-40.0f, 40.0f) * 0.3f;
  particle.dy = get_random(-40.0f, 40.0f) * 0.2f;
  particle.dz = get_random(0.0f, 5.0f) * 0.7f + 2.0f;

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
      particle.x += particle.dx * dt;
      particle.y += particle.dy * dt;
      particle.z += particle.dz * dt;

      if (particle.z < 0)
      {
        particle.z = 0;
        particle.dx *= 0.6f;
        particle.dy *= 0.6f;
        particle.dz *= -0.5f;
      }

      particle.dz -= 0.15f;
    }
  });
}

void render_particles(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::particle>();
  view.each([&](const comp::particle& particle) {
    const cen::frect rect{{particle.x, particle.y - particle.z}, {2.0f, 2.0f}};
    renderer.set_color(particle.color);
    renderer.fill_rect_t(rect);
  });
}

}  // namespace wanderer::sys
