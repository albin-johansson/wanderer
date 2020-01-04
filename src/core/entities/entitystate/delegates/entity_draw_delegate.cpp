#include "entity_draw_delegate.h"
#include "renderer.h"
#include "viewport.h"
#include "entity.h"

namespace albinjohansson::wanderer {

void EntityDrawDelegate::Draw(const Renderer& renderer,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept {
  auto[x, y] = entity.get_interpolated_position();
  auto src = Rectangle(srcX, srcY, 64, 64);
  auto dst = FRectangle(x, y, {entity.get_width(), entity.get_height()});
  renderer.RenderTextureTranslated(entity.GetSpriteSheet(), src, dst);
}

}
