#include "humanoid_factory_system.hpp"

#include <cassert>
#include <counter.hpp>
#include <texture.hpp>

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
#include "image_loader.hpp"

namespace wanderer::sys::humanoid {
namespace {

/**
 * @brief Adds a humanoid entity to the registry and returns the associated
 * identifier.
 *
 * @details The entity will have `movable`, `depth_drawable`, `animated`,
 * `humanoid` and `humanoid_idle` components added to it. Select components
 * will have default values assigned to them, which might have to be tweaked
 * for the specific humanoid.
 *
 * @pre `texture` must be a valid handle.
 *
 * @param registry the registry that will be used.
 * @param texture the handle to the texture that will be used by the humanoid.
 *
 * @return the identifier associated with the created humanoid.
 */
[[nodiscard]] auto create_basic_humanoid(
    entt::registry& registry,
    const entt::handle<cen::texture>& texture) -> entt::entity
{
  assert(texture);  // require valid handle

  const auto entity = registry.create();

  auto& movable = registry.emplace<comp::movable>(entity);
  movable.dominantDirection = direction::down;

  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = texture;
  drawable.src = {{0, 0}, {64, 64}};
  drawable.dst = {{0, 0}, {g_humanoidDrawWidth, g_humanoidDrawHeight}};

  using ms = cen::milliseconds<u32>;

  auto& animated = registry.emplace<comp::animated>(entity);
  animated.frame = 0;
  animated.delay = ms{65};
  animated.then = cen::counter::ticks();
  animated.nFrames = 1;

  constexpr cen::farea humanoidSize{g_humanoidDrawWidth, g_humanoidDrawHeight};

  registry.emplace<comp::hitbox>(
      entity,
      hitbox::create(
          {comp::subhitbox{vector2f{}, cen::frect{{}, humanoidSize}}}));

  registry.emplace<comp::humanoid>(entity);
  registry.emplace<comp::humanoid_idle>(entity);

  return entity;
}

}  // namespace

auto add_player(entt::registry& registry,
                cen::renderer& renderer,
                image_cache& imageCache) -> entt::entity
{
  constexpr auto id = "player"_hs;
  if (!imageCache.contains(id)) {
    imageCache.load<image_loader>(id, renderer, "resource/img/player2.png");
  }

  const auto playerEntity =
      create_basic_humanoid(registry, imageCache.handle(id));

  registry.emplace<comp::player>(playerEntity);

  auto& movable = registry.get<comp::movable>(playerEntity);
  movable.speed = g_playerSpeed;
  movable.position = {100, 100};
  movable.dominantDirection = direction::down;

  registry.emplace<comp::binds>(playerEntity);

  return playerEntity;
}

auto add_skeleton(entt::registry& registry,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> entt::entity
{
  constexpr auto id = "skeleton"_hs;
  if (!imageCache.contains(id)) {
    imageCache.load<image_loader>(id, renderer, "resource/img/skeleton.png");
  }

  const auto skeletonEntity =
      create_basic_humanoid(registry, imageCache.handle(id));

  auto& movable = registry.get<comp::movable>(skeletonEntity);
  movable.speed = g_monsterSpeed;
  movable.position = {300, 300};

  return skeletonEntity;
}

}  // namespace wanderer::sys::humanoid
