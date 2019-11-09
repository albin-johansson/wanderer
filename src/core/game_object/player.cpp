#include "player.h"
#include "game_object_delegate.h"
#include "movable_delegate.h"
#include <memory>

namespace wanderer::core {

Player::Player() {
  gameObject = std::make_unique<GameObjectDelegate>();
  movable = std::make_unique<MovableDelegate>();
}

void Player::Tick(float delta) {
  movable->Tick(delta);
}

void Player::Draw(view::Renderer& renderer) const noexcept {
  renderer.SetColor(0xFF, 0, 0);
  renderer.RenderFillRect(GetX(), GetY(), GetWidth(), GetHeight());
}

}
