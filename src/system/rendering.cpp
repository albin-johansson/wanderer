#include "rendering.h"

#include <colors.h>

#include "movable.h"
#include "player.h"

using namespace centurion;

namespace wanderer {

void render_player(Registry& registry, Renderer& renderer)
{
  const auto group = registry.group<Player>(entt::get<Movable>);
  for (const Entity entity : group) {
    const auto& movable = group.get<Movable>(entity);
    const auto [x, y] = movable.interpolatedPos;
    const FRect rect = {{x, y}, {100, 100}};
    renderer.set_color(color::red);
    renderer.fill_rect_tf(rect);

    //    const auto& [x, y] = entity.get_interpolated_position();
    //    const auto src = IRect{srcX, srcY, 64, 64};
    //    const auto dst = FRect{x, y, entity.get_width(), entity.get_height()};
    //    renderer.render_tf(entity.get_sprite_sheet(), src, dst);
  }
}

}  // namespace wanderer
