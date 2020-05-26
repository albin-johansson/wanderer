#include "make_player.h"

#include "player.h"
#include "position.h"

namespace wanderer {

Entity make_player(Registry& registry)
{
  Entity player = registry.create();
  registry.emplace<Player>(player);
  registry.emplace<Position>(player, Vector2f{100, 100});

  // TODO add facing direction, health, velocity

  return player;
}

}  // namespace wanderer
