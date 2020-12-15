#include "humanoid_factory_system.hpp"

#include <cassert>  // assert
#include <cen/counter.hpp>
#include <utility>  // move

#include "animated.hpp"
#include "binds.hpp"
#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "direction.hpp"
#include "game_constants.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "humanoid_state.hpp"
#include "movable.hpp"
#include "texture_handle.hpp"

namespace wanderer::sys::humanoid {
namespace {

void add_movable(entt::registry& registry, const entt::entity entity)
{
  auto& movable = registry.emplace<comp::movable>(entity);
  movable.dir = direction::down;
}

void add_depth_drawable(entt::registry& registry,
                        const entt::entity entity,
                        texture_handle texture)
{
  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = std::move(texture);
  drawable.src = {{0, 0}, {64, 64}};
  drawable.dst = {{0, 0}, glob::humanoidDrawSize<>};
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
                const vector2f& position)
{
  auto hitbox = hitbox::create({{{18, 32}, {28, 24}}});
  sys::hitbox::set_position(hitbox, position);

  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);

  registry.emplace<comp::hitbox>(entity, hitbox);
}

/**
 * \brief Adds a humanoid entity to the registry and returns the associated
 * identifier.
 *
 * \details The entity will have `movable`, `depth_drawable`, `animated`,
 * `hitbox`, `humanoid` and `humanoid_idle` components added to it. Select
 * components will have default values assigned to them, which might have to be
 * tweaked for the specific humanoid.
 *
 * \pre `texture` must be a valid handle.
 *
 * \param registry the registry that will be used.
 * \param texture the handle to the texture that will be used by the humanoid.
 *
 * \return the identifier associated with the created humanoid.
 */
[[nodiscard]] auto make_humanoid(entt::registry& registry,
                                 aabb_tree& tree,
                                 const texture_handle& texture) -> entt::entity
{
  assert(texture);  // require valid handle

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

auto add_player(entt::registry& registry,
                aabb_tree& tree,
                const vector2f& position,
                graphics_context& graphics) -> entt::entity
{
  constexpr auto id = "player"_hs;
  const auto handle = graphics.load_texture(id, "resource/img/player2.png");

  const auto player = make_humanoid(registry, tree, handle);
  registry.emplace<comp::player>(player);

  auto& movable = registry.get<comp::movable>(player);
  movable.speed = glob::playerSpeed;
  movable.position = position;
  movable.dir = direction::down;

  registry.emplace<comp::binds>(player);

  return player;
}

auto add_skeleton(entt::registry& registry,
                  aabb_tree& tree,
                  const vector2f& position,
                  graphics_context& graphics) -> entt::entity
{
  constexpr auto id = "skeleton"_hs;
  const auto handle = graphics.load_texture(id, "resource/img/skeleton.png");

  const auto skeleton = make_humanoid(registry, tree, handle);

  auto& movable = registry.get<comp::movable>(skeleton);
  movable.speed = glob::monsterSpeed;
  movable.position = position;

  return skeleton;
}

}  // namespace wanderer::sys::humanoid
