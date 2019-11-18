#include "entity_draw_delegate.h"

namespace wanderer::core {

void EntityDrawDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport,
                              const IEntity& entity, float srcX, float srcY) noexcept {
  Vector2 interpolatedPosition = entity.GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());
  auto src = Rectangle(srcX, srcY, 64, 64);
  auto dst = Rectangle(x, y, entity.GetWidth(), entity.GetHeight());
  renderer.RenderTexture(entity.GetSpriteSheet().GetTexture(), src, dst);
}

}
