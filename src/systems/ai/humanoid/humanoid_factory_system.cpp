#include "humanoid_factory_system.hpp"

#include <cassert>  // assert
#include <utility>  // move

#include <centurion.hpp>  // ticks

#include "components/animation.hpp"
#include "components/chase.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "components/point_light.hpp"
#include "components/roam.hpp"
#include "core/direction.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/physics/hitbox_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

constexpr int32 humanoid_source_width = 64;
constexpr int32 humanoid_source_height = 64;

void AddMovable(entt::registry& registry, const entt::entity entity)
{
  auto& movable = registry.emplace<Movable>(entity);
  movable.dir = Direction::Down;
}

void AddDepthDrawable(entt::registry& registry,
                      const entt::entity entity,
                      const usize texture)
{
  auto& drawable = registry.emplace<Drawable>(entity);
  drawable.texture = texture;
  drawable.src = {{}, {humanoid_source_width, humanoid_source_height}};
  drawable.dst = {{}, glob::humanoid_draw_size};
}

void AddAnimated(entt::registry& registry, const entt::entity entity)
{
  using namespace cen::literals;

  auto& animation = registry.emplace<Animation>(entity);
  animation.frame = 0;
  animation.delay = 65_ms;
  animation.then = cen::counter::ticks();
  animation.frame_count = 1;
}

void AddHitbox(Level& level, const entt::entity entity, const float2 position)
{
  constexpr auto x0 = 0.5625f * glob::tile_width<>;
  constexpr auto x1 = 0.875f * glob::tile_width<>;
  constexpr auto y0 = glob::tile_height<>;
  constexpr auto y1 = 0.75f * glob::tile_height<>;

  auto hitbox = MakeHitbox({{{x0, y0}, {x1, y1}}});
  sys::SetPosition(hitbox, position);

  const auto lower = ToRuneVector(hitbox.bounds.position());
  const auto upper = lower + ToRuneVector(hitbox.bounds.size());
  level.tree.insert(entity, lower, upper);

  level.registry.emplace<Hitbox>(entity, hitbox);
}

[[nodiscard]] auto MakeHumanoid(Level& level, const usize texture) -> entt::entity
{
  const auto entity = level.registry.create();

  level.registry.emplace<Humanoid>(entity);
  level.registry.emplace<HumanoidIdle>(entity);

  AddMovable(level.registry, entity);
  AddDepthDrawable(level.registry, entity, texture);
  AddAnimated(level.registry, entity);
  AddHitbox(level, entity, {0, 0});  // FIXME position

  return entity;
}

void AddLight(entt::registry& registry, const entt::entity entity, const float2 position)
{
  auto& light = registry.emplace<PointLight>(entity);
  light.size = 160;
  light.position = position;
  light.fluctuation = 0;
  light.fluctuation_step = 0;
  light.fluctuation_limit = 0;
}

}  // namespace

auto MakePlayer(Level& level, GraphicsContext& graphics) -> entt::entity
{
  constexpr uint32 id = "player"_hs;
  static const auto path = GetTextureResource("player.png");

  const auto texture = graphics.LoadTexture(id, path);
  const auto player = MakeHumanoid(level, texture);

  auto& movable = level.registry.get<Movable>(player);
  movable.speed = glob::player_speed;
  movable.position = level.player_spawn_position.value();

  AddLight(level.registry, player, movable.position);

  level.registry.emplace<Player>(player);

  return player;
}

auto MakeSkeleton(Level& level, float2 position, GraphicsContext& graphics)
    -> entt::entity
{
  constexpr uint32 id = "skeleton"_hs;
  static const auto path = GetTextureResource("skeleton.png");

  const auto texture = graphics.LoadTexture(id, path);
  const auto skeleton = MakeHumanoid(level, texture);

  auto& movable = level.registry.get<Movable>(skeleton);
  movable.speed = glob::monster_speed;
  movable.position = position;

  auto& chase = level.registry.emplace<Chase>(skeleton);
  chase.target = singleton_entity<Player>(level.registry);
  chase.range = 150;

  auto& roam = level.registry.emplace<Roam>(skeleton);
  roam.cooldown_duration = 100;

  return skeleton;
}

}  // namespace wanderer::sys
