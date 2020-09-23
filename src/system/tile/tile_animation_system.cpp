#include "tile_animation_system.hpp"

#include <counter.hpp>

#include "animated_tile.hpp"

namespace wanderer::sys::tile {

void update_animation(entt::registry& registry, entt::entity /*level*/)  // TODO
{
  const auto entities = registry.view<comp::AnimatedTile>();
  for (const auto entity : entities) {
    auto& animatedTile = entities.get<comp::AnimatedTile>(entity);

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
