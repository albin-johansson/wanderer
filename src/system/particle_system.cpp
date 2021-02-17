#include "particle_system.hpp"

#include <cen/counter.hpp>

#include "get_random.hpp"
#include "particle.hpp"

namespace wanderer::sys {

void add_particle(entt::registry& registry, const vector2f& position)
{
  using namespace cen::literals;

  auto& particle = registry.emplace<comp::particle>(registry.create());
  particle.x = position.x;
  particle.y = position.y;
  particle.z = 2;
  particle.dx = get_random(-50.0f, 50.0f) * 0.3f;
  particle.dy = get_random(-50.0f, 50.0f) * 0.2f;
  particle.dz = get_random(0.0f, 10.0f) * 0.7f + 2.0f;
  particle.start = cen::counter::ticks();
  particle.duration = 3'000_ms;
}

void update_particles(entt::registry& registry, const delta_t dt)
{
  const auto delta = static_cast<float>(dt.get());
  const auto view = registry.view<comp::particle>();

  const auto now = cen::counter::ticks();

  view.each([&](const entt::entity entity, comp::particle& particle) {
    const auto duration = now - particle.start;
    if (duration >= particle.duration) {
      registry.destroy(entity);
    } else {
      // Stop particle after 3/4 of duration has passed
      if (duration >= particle.duration * 0.75f) {
        particle.dx = 0;
        particle.dy = 0;
        particle.dz = 0;
      } else {
        particle.x += particle.dx * delta;
        particle.y += particle.dy * delta;
        particle.z += particle.dz * delta;

        if (particle.z < 0) {
          particle.z = 0;
          particle.dx *= 0.6f;
          particle.dy *= 0.6f;
          particle.dz *= -0.5f;
        }

        particle.dz -= 0.75f * delta;
      }
    }
  });
}

void render_particles(const entt::registry& registry, cen::renderer& renderer)
{
  renderer.set_color(cen::colors::red);

  const auto view = registry.view<const comp::particle>();
  view.each([&](const comp::particle& particle) {
    const cen::frect rect{{particle.x, particle.y - particle.z}, {5.0f, 5.0f}};
    renderer.fill_rect_t(rect);
  });
}

}  // namespace wanderer::sys
