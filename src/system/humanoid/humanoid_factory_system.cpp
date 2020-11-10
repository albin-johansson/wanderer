#include "humanoid_factory_system.hpp"

#include <cassert>
#include <cen/counter.hpp>
#include <cen/texture.hpp>
#include <cen/types.hpp>

#include "component/animated.hpp"
#include "component/binds.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/humanoid_state.hpp"
#include "component/movable.hpp"
#include "component/player.hpp"
#include "direction.hpp"
#include "game_constants.hpp"
#include "hitbox_system.hpp"
#include "texture_handle.hpp"
#include "texture_loader.hpp"

namespace wanderer::sys::humanoid {
namespace {

/**
 * \brief Adds a humanoid entity to the registry and returns the associated
 * identifier.
 *
 * \details The entity will have `movable`, `depth_drawable`, `animated`,
 * `humanoid` and `humanoid_idle` components added to it. Select components
 * will have default values assigned to them, which might have to be tweaked
 * for the specific humanoid.
 *
 * \pre `texture` must be a valid handle.
 *
 * \param registry the registry that will be used.
 * \param texture the handle to the texture that will be used by the humanoid.
 *
 * \return the identifier associated with the created humanoid.
 */
[[nodiscard]] auto make_basic_humanoid(entt::registry& registry,
                                       abby::aabb_tree<entt::entity>& aabbTree,
                                       const texture_handle& texture)
    -> entt::entity
{
  assert(texture);  // require valid handle

  using namespace cen::literals;
  constexpr cen::farea humanoidSize{g_humanoidDrawWidth, g_humanoidDrawHeight};

  const auto entity = registry.create();

  auto& movable = registry.emplace<comp::movable>(entity);
  movable.dominantDirection = direction::down;

  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = texture;
  drawable.src = {{0, 0}, {64, 64}};
  drawable.dst = {{0, 0}, humanoidSize};

  auto& animated = registry.emplace<comp::animated>(entity);
  animated.frame = 0;
  animated.delay = 65_ms;
  animated.then = cen::counter::ticks();
  animated.nFrames = 1;

  aabbTree.emplace(entity,
                   abby_vector(movable.position),
                   abby_vector(g_humanoidDrawSize));

  // FIXME
  const auto hitbox =
      hitbox::create({comp::subhitbox{{}, cen::frect{{}, humanoidSize}}});

  registry.emplace<comp::hitbox>(entity, hitbox);
  registry.emplace<comp::humanoid>(entity);
  registry.emplace<comp::humanoid_idle>(entity);

  return entity;
}

}  // namespace

auto add_player(entt::registry& registry,
                abby::aabb_tree<entt::entity>& aabbTree,
                const vector2f& position,
                cen::renderer& renderer,
                texture_cache& cache) -> entt::entity
{
  constexpr auto id = "player"_hs;
  const auto handle =
      cache.load<texture_loader>(id, renderer, "resource/img/player2.png");
  assert(handle);

  const auto player = make_basic_humanoid(registry, aabbTree, handle);
  registry.emplace<comp::player>(player);

  auto& movable = registry.get<comp::movable>(player);
  movable.speed = g_playerSpeed;
  movable.position = position;
  movable.dominantDirection = direction::down;

  registry.emplace<comp::binds>(player);

  return player;
}

auto add_skeleton(entt::registry& registry,
                  abby::aabb_tree<entt::entity>& aabbTree,
                  const vector2f& position,
                  cen::renderer& renderer,
{
  constexpr auto id = "skeleton"_hs;
  const auto handle =
      cache.load<texture_loader>(id, renderer, "resource/img/skeleton.png");

  const auto skeleton = make_basic_humanoid(registry, aabbTree, handle);

  auto& movable = registry.get<comp::movable>(skeleton);
  movable.speed = g_monsterSpeed;
  movable.position = position;

  return skeleton;
}

}  // namespace wanderer::sys::humanoid
