#include "physics_system.hpp"

#include "wanderer/core/centurion_utils.hpp"
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
                      const float32 maxSpeed,
                      const glm::vec2& offset)
{
  WANDERER_ASSERT(entity != entt::null);
  WANDERER_ASSERT(!registry.all_of<comp::PhysicsBody>(entity));

  auto& world = registry.ctx().at<comp::PhysicsWorld>();

  b2BodyDef bodyDef;
  bodyDef.position = sys::to_physics_scale(registry, logicalPos + offset);
  bodyDef.type = type;
  bodyDef.fixedRotation = true;
  bodyDef.gravityScale = 0;

  auto& body = registry.emplace<comp::PhysicsBody>(entity);
  body.data = world.simulation.CreateBody(&bodyDef);
  body.offset = sys::to_physics_scale(registry, offset);
  body.size = sys::to_physics_scale(registry, logicalSize);
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
  WANDERER_ASSERT(registry.all_of<comp::PhysicsBody>(entity));

  auto& world = registry.ctx().at<comp::PhysicsWorld>();
  auto& body = registry.get<comp::PhysicsBody>(entity);

  world.simulation.DestroyBody(body.data);
}

void update_physics(entt::registry& registry, const float32 dt)
{
  auto& world = registry.ctx().at<comp::PhysicsWorld>();
  world.simulation.Step(dt, _n_velocity_iterations, _n_position_iterations);

  for (auto&& [entity, object, body] :
       registry.view<comp::GameObject, comp::PhysicsBody>().each()) {
    auto pos = glmx::from_b2(body.data->GetPosition() - body.offset);
    object.position = pos / world.scale;
  }
}

void debug_physics(const entt::registry& registry, Graphics& graphics)
{
  const auto& viewport = registry.ctx().at<comp::Viewport>();
  const auto viewportRect = as_rect(viewport.offset, viewport.size);

  auto& renderer = graphics.renderer();
  renderer.set_color(cen::colors::magenta);

  for (auto&& [entity, body] : registry.view<comp::PhysicsBody>().each()) {
    const auto position = to_logical_scale(registry, body.data->GetPosition());
    const auto size = to_logical_scale(registry, body.size);

    cen::frect hitbox{position.x, position.y, size.x, size.y};
    if (cen::intersects(viewportRect, hitbox)) {
      hitbox.offset_x(-viewport.offset.x);
      hitbox.offset_y(-viewport.offset.y);

      renderer.draw_rect(hitbox);
    }
  }
}

auto to_physics_scale(const entt::registry& registry, const glm::vec2& vec) -> b2Vec2
{
  const auto& physics = registry.ctx().at<comp::PhysicsWorld>();
  return {vec.x * physics.scale.x, vec.y * physics.scale.y};
}

auto to_logical_scale(const entt::registry& registry, const b2Vec2& vec) -> glm::vec2
{
  const auto& physics = registry.ctx().at<comp::PhysicsWorld>();
  return {vec.x / physics.scale.x, vec.y / physics.scale.y};
}

}  // namespace wanderer::sys