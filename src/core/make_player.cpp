#include "make_player.h"

#include "collision.h"
#include "movable.h"
#include "player.h"
#include "entity_state.h"

namespace wanderer {

entt::entity make_player(entt::registry& registry)
{
  entt::entity player = registry.create();
  registry.emplace<Player>(player);

  auto& movable = registry.emplace<Movable>(player);
  movable.speed = 230;
  movable.currentPos.x = 100;
  movable.currentPos.y = 100;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  registry.emplace<Collision>(player);
  registry.emplace<EntityIdleState>(player);

  // TODO add facing direction, health,

  return player;
}

}  // namespace wanderer
