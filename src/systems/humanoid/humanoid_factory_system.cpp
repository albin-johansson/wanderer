#include "humanoid_factory_system.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // ticks
#include <utility>        // move

#include "components/chase.hpp"
#include "components/graphics/animated.hpp"
#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/point_light.hpp"
#include "components/hitbox.hpp"
#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "core/direction.hpp"
#include "core/game_constants.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/movement/hitbox_system.hpp"

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
  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = texture;
  drawable.src = {{}, {humanoid_source_width, humanoid_source_height}};
  drawable.dst = {{}, glob::humanoid_draw_size<>};
}

void add_animated(entt::registry& registry, const entt::entity entity)
{
  using namespace cen::literals;

  auto& animated = registry.emplace<comp::animated>(entity);
  animated.frame = 0;
  animated.delay = 65_ms;
  animated.then = cen::counter::ticks();
  animated.nFrames = 1;
}

void add_hitbox(entt::registry& registry,
                const entt::entity entity,
                aabb_tree& tree,
                const float2 position)
{
  constexpr auto x0 = 0.5625f * glob::tile_width<>;
  constexpr auto x1 = 0.875f * glob::tile_width<>;
  constexpr auto y0 = glob::tile_height<>;
  constexpr auto y1 = 0.75f * glob::tile_height<>;

  auto hitbox = create_hitbox({{{x0, y0}, {x1, y1}}});
  sys::set_position(hitbox, position);

  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);

  registry.emplace<comp::hitbox>(entity, hitbox);
}

/**
 * \brief Creates a humanoid entity.
 *
 * \details The entity will have `movable`, `depth_drawable`, `animated`,
 * `hitbox`, `humanoid` and `humanoid_idle` components added to it. Select
 * components will have default values assigned to them, whilst others might have to be
 * tweaked for the specific humanoid.
 *
 * \param registry the registry that will be used.
 * \param texture the index of the texture that will be used by the humanoid.
 *
 * \return the created entity.
 */
[[nodiscard]] auto make_humanoid(entt::registry& registry,
                                 aabb_tree& tree,
                                 const texture_index texture) -> entt::entity
{
  const auto entity = registry.create();

  registry.emplace<comp::humanoid>(entity);
  registry.emplace<comp::humanoid_idle>(entity);

  add_movable(registry, entity);
  add_depth_drawable(registry, entity, texture);
  add_animated(registry, entity);
  add_hitbox(registry, entity, tree, {0, 0});  // FIXME position

  return entity;
}

}  // namespace

auto make_player(entt::registry& registry,
                 aabb_tree& tree,
                 const float2 position,
                 graphics_context& graphics) -> entt::entity
{
  static const auto path = resources::texture("player.png");
  const auto texture = graphics.load("player"_hs, path);
  const auto player = make_humanoid(registry, tree, texture);

  auto& movable = registry.get<comp::movable>(player);
  movable.speed = glob::player_speed;
  movable.position = position;
  movable.dir = direction::down;

  auto& light = registry.emplace<comp::point_light>(player);
  light.size = 160;
  light.position = position;
  light.fluctuation = 0;
  light.fluctuationStep = 0;
  light.fluctuationLimit = 0;

  return player;
}

auto make_skeleton(entt::registry& registry,
                   aabb_tree& tree,
                   const float2 position,
                   graphics_context& graphics) -> entt::entity
{
  static const auto path = resources::texture("skeleton.png");
  const auto texture = graphics.load("skeleton"_hs, path);
  const auto skeleton = make_humanoid(registry, tree, texture);

  auto& movable = registry.get<comp::movable>(skeleton);
  movable.speed = glob::monster_speed;
  movable.position = position;
  movable.dir = direction::down;

  auto& chase = registry.emplace<comp::chase>(skeleton);
  chase.target = registry.ctx<ctx::player>().entity;
  chase.range = 150;

  return skeleton;
}

}  // namespace wanderer::sys
