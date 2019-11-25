#include "entity_draw_delegate.h"

namespace albinjohansson::wanderer {

void EntityDrawDelegate::Draw(Renderer& renderer, const Viewport& viewport,
                              const IEntity& entity, float srcX, float srcY) noexcept {
  Vector2 interpolatedPosition = entity.GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());
  auto src = Rectangle(srcX, srcY, 64, 64);
  auto dst = Rectangle(x, y, entity.GetWidth(), entity.GetHeight());
  renderer.RenderTexture(entity.GetSpriteSheet(), src, dst);

  auto hbWidth = (static_cast<float>(entity.GetHealth()) / 100.0f) * 120.0f;
  auto hbX = (x + (entity.GetWidth() / 2.0f)) - (hbWidth / 2);
  renderer.SetColor(0xff, 0, 0);
  renderer.RenderFillRect(hbX, y, hbWidth, 5.0f);
}

}
