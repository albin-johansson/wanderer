#include "humanoid_factory_system.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // ticks
#include <utility>        // move

#include "components/ai/chase.hpp"
#include "components/ai/humanoid.hpp"
#include "components/ai/roam.hpp"
#include "components/gfx/animation.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/physics/hitbox.hpp"
#include "components/physics/movable.hpp"
#include "core/direction.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/physics/hitbox_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline constexpr int humanoid_source_width = 64;
inline constexpr int humanoid_source_height = 64;

void add_movable(entt::registry& registry, const entt::entity entity)
{
  auto& movable = registry.emplace<comp::movable>(entity);
  movable.dir = direction::down;
}

void add_depth_drawable(entt::registry& registry,
                        const entt::entity entity,
                        const texture_index texture)
{
  auto& drawable = registry.emplace<comp::drawable>(entity);
  drawable.texture = texture;
  drawable.src = {{}, {humanoid_source_width, humanoid_source_height}};
  drawable.dst = {{}, glob::humanoid_draw_size};
}

void add_animated(entt::registry& registry, const entt::entity entity)
{
  using namespace cen::literals;

  auto& animation = registry.emplace<comp::animation>(entity);
  animation.frame = 0;
  animation.delay = 65_ms;
  animation.then = cen::counter::ticks();
  animation.frame_count = 1;
}

void add_hitbox(comp::level& level, const entt::entity entity, const float2 position)
{
  constexpr auto x0 = 0.5625f * glob::tile_width<>;
  constexpr auto x1 = 0.875f * glob::tile_width<>;
  constexpr auto y0 = glob::tile_height<>;
  constexpr auto y1 = 0.75f * glob::tile_height<>;

  auto hitbox = make_hitbox({{{x0, y0}, {x1, y1}}});
  sys::set_position(hitbox, position);

  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  level.tree.insert(entity, lower, upper);

  level.registry.emplace<comp::hitbox>(entity, hitbox);
}

[[nodiscard]] auto make_humanoid(comp::level& level, const texture_index texture)
    -> entt::entity
{
  const auto entity = level.registry.create();

  level.registry.emplace<comp::humanoid>(entity);
  level.registry.emplace<comp::humanoid_idle>(entity);

  add_movable(level.registry, entity);
  add_depth_drawable(level.registry, entity, texture);
  add_animated(level.registry, entity);
  add_hitbox(level, entity, {0, 0});  // FIXME position

  return entity;
}

void add_light(entt::registry& registry, const entt::entity entity, const float2 position)
{
  auto& light = registry.emplace<comp::point_light>(entity);
  light.size = 160;
  light.position = position;
  light.fluctuation = 0;
  light.fluctuation_step = 0;
  light.fluctuation_limit = 0;
}

}  // namespace

auto make_player(comp::level& level, graphics_context& graphics) -> entt::entity
{
  constexpr auto id = texture_id{"player"_hs};
  static const auto path = resources::texture("player.png");

  const auto texture = graphics.load(id, path);
  const auto player = make_humanoid(level, texture);

  auto& movable = level.registry.get<comp::movable>(player);
  movable.speed = glob::player_speed;
  movable.position = level.player_spawn_position.value();

  add_light(level.registry, player, movable.position);

  level.registry.emplace<comp::player>(player);

  return player;
}

auto make_skeleton(comp::level& level, const float2 position, graphics_context& graphics)
    -> entt::entity
{
  constexpr auto id = texture_id{"skeleton"_hs};
  static const auto path = resources::texture("skeleton.png");

  const auto texture = graphics.load(id, path);
  const auto skeleton = make_humanoid(level, texture);

  auto& movable = level.registry.get<comp::movable>(skeleton);
  movable.speed = glob::monster_speed;
  movable.position = position;

  auto& chase = level.registry.emplace<comp::chase>(skeleton);
  chase.target = singleton_entity<comp::player>(level.registry);
  chase.range = 150;

  auto& roam = level.registry.emplace<comp::roam>(skeleton);
  roam.cooldown_duration = 100;

  return skeleton;
}

}  // namespace wanderer::sys
