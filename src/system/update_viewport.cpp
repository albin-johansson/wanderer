#include "update_viewport.h"

#include "game_constants.h"
#include "movable.h"
#include "viewport.h"

namespace wanderer {

void update_viewport(entt::registry& registry,
                     entt::entity viewport,
                     entt::entity player,
                     float delta)
{
  if (const auto* movable = registry.try_get<Movable>(player); movable) {
    if (auto* view = registry.try_get<Viewport>(viewport); view) {
      view->track(movable->interpolatedPos,
                  {g_entityDrawWidth, g_entityDrawHeight},
                  delta);
    }
  }
}

}  // namespace wanderer
