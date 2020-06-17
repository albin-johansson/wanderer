#include "humanoid_factory_system.h"

#include <texture.h>

#include "animated.h"
#include "binds.h"
#include "collision.h"
#include "depth_drawable.h"
#include "direction.h"
#include "game_constants.h"
#include "movable.h"
#include "player.h"

using centurion::Renderer;
using centurion::Texture;

namespace wanderer::system::humanoid {

entt::entity add_player(entt::registry& registry, Renderer& renderer)
{
  entt::entity playerEntity = registry.create();

  registry.emplace<Player>(playerEntity);

  auto& movable = registry.emplace<Movable>(playerEntity);
  movable.speed = g_playerSpeed;
  movable.currentPos.x = 100;
  movable.currentPos.y = 100;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  auto& drawable = registry.emplace<DepthDrawable>(playerEntity);
  drawable.texture = Texture::shared(renderer, "resource/img/player2.png");

  auto& animated = registry.emplace<Animated>(playerEntity);
  animated.nFrames = 5;  // FIXME

  registry.emplace<Collision>(playerEntity);
  registry.emplace<Binds>(playerEntity);
  registry.emplace<Humanoid>(playerEntity);
  registry.emplace<HumanoidIdle>(playerEntity);

  return playerEntity;
}

entt::entity add_skeleton(entt::registry& registry, Renderer& renderer)
{
  entt::entity skeletonEntity = registry.create();

  auto& movable = registry.emplace<Movable>(skeletonEntity);
  movable.speed = g_playerSpeed;  // FIXME
  movable.currentPos.x = 300;
  movable.currentPos.y = 300;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  auto& drawable = registry.emplace<DepthDrawable>(skeletonEntity);
  drawable.texture = Texture::shared(renderer, "resource/img/skeleton.png");
  drawable.depth = 7;

  auto& animated = registry.emplace<Animated>(skeletonEntity);
  animated.nFrames = 4;  // FIXME

  registry.emplace<Collision>(skeletonEntity);
  registry.emplace<Humanoid>(skeletonEntity);
  registry.emplace<HumanoidIdle>(skeletonEntity);

  return skeletonEntity;
}

}  // namespace wanderer::system::humanoid
