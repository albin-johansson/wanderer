#include "physics_system.hpp"

#include "wanderer/core/graphics.hpp"
#include "wanderer/core/math.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

/* These are the values recommended in the Box2D docs, so they should be fine! */
constexpr int32 _n_velocity_iterations = 8;
constexpr int32 _n_position_iterations = 3;

}  // namespace

void add_physics_body(entt::registry& registry,
                      const entt::entity entity,
                      const b2BodyType type,
                      const glm::vec2& logicalPos,
                      const glm::vec2& logicalSize,
                      const float32 maxSpeed)
{
  WANDERER_ASSERT(entity != entt::null);
  WANDERER_ASSERT(!registry.all_of<comp::physics_body>(entity));

  auto& world = registry.ctx<comp::physics_world>();

  b2BodyDef bodyDef;
  bodyDef.position = sys::to_physics_world(registry, logicalPos);
  bodyDef.type = type;
  bodyDef.fixedRotation = true;
  bodyDef.gravityScale = 0;

  auto& body = registry.emplace<comp::physics_body>(entity);
  body.data = world.simulation.CreateBody(&bodyDef);
  body.size = sys::to_physics_world(registry, logicalSize);
  body.max_speed = maxSpeed;

  const b2Vec2 center{body.size.x / 2.0f, body.size.y / 2.0f};

  b2PolygonShape shape;
  shape.SetAsBox(body.size.x / 2.0f, body.size.y / 2.0f, center, 0);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = (type == b2_dynamicBody) ? 1.0f : 0.0f;
  fixtureDef.friction = 0;

  body.data->CreateFixture(&fixtureDef);
}

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
  world.simulation.Step(dt, _n_velocity_iterations, _n_position_iterations);

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
  renderer.set_color(cen::colors::magenta);

  for (auto&& [entity, body] : registry.view<comp::physics_body>().each()) {
    const auto position = to_logical_world(registry, body.data->GetPosition());
    const auto size = to_logical_world(registry, body.size);

    const cen::frect hitbox{position.x - viewport.offset.x,
                            position.y - viewport.offset.y,
                            size.x,
                            size.y};
    renderer.draw_rect(hitbox);
  }
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