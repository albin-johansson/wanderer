#include "tile_animation_system.h"

#include <counter.hpp>

#include "animated_tile.h"

using wanderer::comp::AnimatedTile;

namespace wanderer::sys::tile {

void update_animation(entt::registry& registry, entt::entity /*level*/)  // TODO
{
  const auto entities = registry.view<AnimatedTile>();
  for (const auto entity : entities) {
    auto& animatedTile = entities.get<AnimatedTile>(entity);

    const auto now = cen::counter::ticks().count();  // FIXME don't .count()
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

}  // namespace wanderer::sys::tile
