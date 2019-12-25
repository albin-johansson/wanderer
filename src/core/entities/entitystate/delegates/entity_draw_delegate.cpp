#include "entity_draw_delegate.h"
#include "renderer.h"
#include "viewport.h"
#include "entity.h"

namespace albinjohansson::wanderer {

void EntityDrawDelegate::Draw(Renderer& renderer,
                              const Viewport& viewport,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept {
  auto[ix, iy] = entity.GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(ix);
  auto y = viewport.GetTranslatedY(iy);

  auto src = Rectangle(srcX, srcY, 64, 64);
  auto dst = FRectangle(x, y, entity.GetWidth(), entity.GetHeight());
  renderer.RenderTexture(entity.GetSpriteSheet(), src, dst);
}

}
