#include "render.h"

#include <colors.h>

#include "player.h"
#include "position.h"

using namespace centurion;

namespace wanderer {

void render_player(Registry& registry, Renderer& renderer, float alpha)
{
  const auto view = registry.view<Player, Position>();
  for (const Entity entity : view) {
    const auto position = view.get<Position>(entity);
    const FRect rect = {{position.x, position.y}, {100, 100}};
    renderer.set_color(color::red);
    renderer.fill_rect_tf(rect);
  }
}

}  // namespace wanderer
