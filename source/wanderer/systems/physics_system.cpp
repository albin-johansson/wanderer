#include "physics_system.hpp"

#include "wanderer/core/graphics.hpp"
#include "wanderer/core/math.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {

void on_destroy_physics_object(entt::registry& registry, const entt::entity entity)
{
  WANDERER_ASSERT(entity != entt::null);
  WANDERER_ASSERT(registry.all_of<comp::physics_body>(entity));

  auto& world = registry.ctx<comp::physics_world>();
  auto& body = registry.get<comp::physics_body>(entity);

  world.simulation.DestroyBody(body.data);
}

void update_physics(entt::registry& registry, const float32 dt)
{
  auto& world = registry.ctx<comp::physics_world>();
  world.simulation.Step(dt, 8, 3);

  for (auto&& [entity, object, body] :
       registry.view<comp::game_object, comp::physics_body>().each()) {
    auto pos = glmx::from_b2(body.data->GetPosition());
    object.position = pos / world.scale;
  }
}

void debug_physics(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& world = registry.ctx<comp::physics_world>();
  const auto& viewport = registry.ctx<comp::viewport>();

  auto& renderer = graphics.renderer();
  renderer.set_color(cen::colors::red);

  for (auto&& [entity, body] : registry.view<comp::physics_body>().each()) {
    const auto position = to_logical_world(registry, body.data->GetPosition());
    const auto size = to_logical_world(registry, body.size);

    const cen::frect hitbox{position.x - viewport.offset.x,
                            position.y - viewport.offset.y,
                            size.x,
                            size.y};
    renderer.draw_rect(hitbox);
  }

  const auto& cfg = registry.ctx<game_cfg>();
  renderer.set_color(cen::colors::white.with_alpha(200));
  renderer.draw_line<int>({0, cfg.logical_size.y / 2},
                          {cfg.logical_size.x, cfg.logical_size.y / 2});
  renderer.draw_line<int>({cfg.logical_size.x / 2, 0},
                          {cfg.logical_size.x / 2, cfg.logical_size.y});
}

auto to_physics_world(const entt::registry& registry, const glm::vec2& vec) -> b2Vec2
{
  const auto& physics = registry.ctx<comp::physics_world>();
  return {vec.x * physics.scale.x, vec.y * physics.scale.y};
}

auto to_logical_world(const entt::registry& registry, const b2Vec2& vec) -> glm::vec2
{
  const auto& physics = registry.ctx<comp::physics_world>();
  return {vec.x / physics.scale.x, vec.y / physics.scale.y};
}

}  // namespace wanderer::sys