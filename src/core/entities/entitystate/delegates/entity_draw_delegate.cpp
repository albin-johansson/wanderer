#include "entity_draw_delegate.h"
#include "renderer.h"
#include "image.h"
#include "viewport.h"
#include "entity.h"

using namespace centurion;

namespace albinjohansson::wanderer {

void EntityDrawDelegate::draw(const Renderer& renderer,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept {
  auto[x, y] = entity.get_interpolated_position();
  auto src = Rectangle{srcX, srcY, 64, 64};
  auto dst = FRectangle{x, y, Area{entity.get_width(), entity.get_height()}};
  renderer.RenderTextureTranslated(entity.get_sprite_sheet(), src, dst);
}

}
