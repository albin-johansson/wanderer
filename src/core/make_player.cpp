#include "make_player.h"

#include "binds.h"
#include "collision.h"
#include "entity_state.h"
#include "game_constants.h"
#include "movable.h"
#include "player.h"

namespace wanderer {

entt::entity make_player(entt::registry& registry)
{
  entt::entity player = registry.create();
  registry.emplace<Player>(player);

  auto& movable = registry.emplace<Movable>(player);
  movable.speed = g_playerSpeed;
  movable.currentPos.x = 100;
  movable.currentPos.y = 100;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  registry.emplace<Collision>(player);
  registry.emplace<Binds>(player);
  registry.emplace<EntityIdleState>(player);

  // TODO add facing direction, health,

  return player;
}

}  // namespace wanderer
