#include "render.h"

#include <colors.h>

#include "movable.h"
#include "player.h"

using namespace centurion;

namespace wanderer {

void render_player(Registry& registry, Renderer& renderer, float alpha)
{
  const auto group = registry.group<Player>(entt::get<Movable>);
  for (const Entity entity : group) {
    const auto& movable = group.get<Movable>(entity);
    const auto& interpolated = movable.interpolatedPos;
    const FRect rect = {{interpolated.x, interpolated.y}, {100, 100}};
    renderer.set_color(color::red);
    renderer.fill_rect_tf(rect);
  }
}

}  // namespace wanderer
