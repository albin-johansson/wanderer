#include "make_player.h"

#include "movable.h"
#include "player.h"

namespace wanderer {

Entity make_player(Registry& registry)
{
  Entity player = registry.create();
  registry.emplace<Player>(player);
  registry.emplace<Movable>(player);

  // TODO add facing direction, health,

  return player;
}

}  // namespace wanderer
