#include "tile_animation_system.h"

#include <timer.h>

#include "animated_tile.h"

namespace wanderer::system::tile {

void update_animation(entt::registry& registry, entt::entity /*level*/)  // TODO
{
  const auto entities = registry.view<AnimatedTile>();
  for (const auto entity : entities) {
    auto& animatedTile = entities.get<AnimatedTile>(entity);

    const auto now = ctn::Timer::millis();
    const auto elapsed = now - animatedTile.then;
    if (elapsed >= animatedTile.frames.at(animatedTile.frame).duration) {
      animatedTile.then = now;
      ++animatedTile.frame;
      if (animatedTile.frame >= animatedTile.frames.size()) {
        animatedTile.frame = 0;
      }
    }
  }
}

}  // namespace wanderer::system::tile
