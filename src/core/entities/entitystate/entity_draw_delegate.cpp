#include "entity_draw_delegate.h"

namespace albinjohansson::wanderer {

void EntityDrawDelegate::Draw(Renderer& renderer, const Viewport& viewport,
                              const IEntity& entity, float srcX, float srcY) noexcept {
  auto[ix, iy] = entity.GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(ix);
  auto y = viewport.GetTranslatedY(iy);
  auto src = Rectangle(srcX, srcY, 64, 64);
  auto dst = Rectangle(x, y, entity.GetWidth(), entity.GetHeight());
  renderer.RenderTexture(entity.GetSpriteSheet(), src, dst);

  // TODO remove
  auto hbWidth = (static_cast<float>(entity.GetHealth()) / 100.0f) * 120.0f;
  auto hbX = (x + (entity.GetWidth() / 2.0f)) - (hbWidth / 2);
  renderer.SetColor(0xff, 0, 0);
  renderer.RenderFillRect(hbX, y, hbWidth, 5.0f);
}

}
