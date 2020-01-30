#include "entity_draw_delegate.h"
#include <renderer.h>
#include <rectangle.h>
#include "viewport.h"
#include "entity.h"

using namespace centurion;

namespace albinjohansson::wanderer {

void EntityDrawDelegate::draw(const Renderer& renderer,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept {
  const auto&[x, y] = entity.get_interpolated_position();
  const auto src = Rect{srcX, srcY, 64, 64};
  const auto dst = FRect{x, y, entity.get_width(), entity.get_height()};
  renderer.draw_image_translated(entity.get_sprite_sheet(), src, dst);
}

}
