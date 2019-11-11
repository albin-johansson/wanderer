#include "player.h"
#include "movable_delegate.h"
#include <memory>

namespace wanderer::core {

Player::Player() {
  movableObject = std::make_unique<MovableObjectDelegate>(200, 200);
}

void Player::Tick(float delta) {
  movableObject->Tick(delta);
}

void Player::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  renderer.SetColor(0, 0, 0);
  Vector2 interpolatedPosition = GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());
  renderer.RenderFillRect(x, y, GetWidth(), GetHeight());
}

}
