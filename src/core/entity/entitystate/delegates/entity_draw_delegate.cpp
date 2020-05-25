#include "entity_draw_delegate.h"

#include <rect.h>
#include <renderer.h>

#include "entity.h"
#include "hitbox.h"
#include "viewport.h"

using namespace centurion;

;

namespace wanderer {

void EntityDrawDelegate::draw(Renderer& renderer,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept
{
  const auto& [x, y] = entity.get_interpolated_position();
  const auto src = IRect{srcX, srcY, 64, 64};
  const auto dst = FRect{x, y, entity.get_width(), entity.get_height()};
  renderer.render_tf(entity.get_sprite_sheet(), src, dst);

#ifdef WANDERER_DEBUG
  // TODO CTN 4.1
  const auto& hb = entity.get_hitbox().get_bounds();
  const auto hx = hb.x() - renderer.translation_viewport().x();
  const auto hy = hb.y() - renderer.translation_viewport().y();

  const FRect box = {hx, hy, hb.width(), hb.height()};

  renderer.set_color(color::red);
  renderer.draw_rect_f(box);
#endif  // WANDERER_DEBUG
}

}  // namespace wanderer
