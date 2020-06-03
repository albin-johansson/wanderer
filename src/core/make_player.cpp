#include "make_player.h"

#include "animated.h"
#include "binds.h"
#include "collision.h"
#include "drawable.h"
#include "entity_state.h"
#include "game_constants.h"
#include "movable.h"
#include "player.h"

using namespace centurion;

namespace wanderer {

entt::entity make_player(entt::registry& registry, Renderer& renderer)
{
  entt::entity player = registry.create();
  registry.emplace<Player>(player);

  auto& movable = registry.emplace<Movable>(player);
  movable.speed = g_playerSpeed;
  movable.currentPos.x = 100;
  movable.currentPos.y = 100;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  auto& drawable = registry.emplace<Drawable>(player);

  drawable.texture = Texture::shared(renderer, "resource/img/player2.png");

  registry.emplace<Animated>(player);
  registry.emplace<Collision>(player);
  registry.emplace<Binds>(player);
  registry.emplace<EntityIdleState>(player);

  return player;
}

}  // namespace wanderer
