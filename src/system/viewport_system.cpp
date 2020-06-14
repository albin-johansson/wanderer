#include "viewport_system.h"

#include "game_constants.h"
#include "movable.h"
#include "viewport.h"

namespace wanderer::system {

void update_viewport(entt::registry& registry,
                     const entt::entity viewport,
                     const entt::entity player,
                     const float delta)
{
  if (const auto* movable = registry.try_get<Movable>(player); movable) {
    if (auto* view = registry.try_get<Viewport>(viewport); view) {
      view->track(movable->interpolatedPos,
                  {g_entityDrawWidth, g_entityDrawHeight},
                  delta);
    }
  }
}

}  // namespace wanderer::system
