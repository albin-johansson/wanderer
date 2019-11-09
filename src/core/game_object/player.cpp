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

void Player::Draw(view::Renderer& renderer) const noexcept {
  renderer.SetColor(0xFF, 0, 0);
  Vector2 interpolatedPosition = GetInterpolatedPosition();
  renderer.RenderFillRect(interpolatedPosition.GetX(),
                          interpolatedPosition.GetY(),
                          GetWidth(),
                          GetHeight());
}

}
