#include "player.h"
#include "movable_delegate.h"
#include "entity_state_machine_impl.h"
#include <memory>

namespace wanderer::core {

Player::Player() {
  movableObject = std::make_unique<MovableObjectDelegate>(200, 200);
  entityStateMachine = std::make_unique<EntityStateMachineImpl>(this);
}

void Player::HandleInput(const Input& input) {
  entityStateMachine->HandleInput(input);
}

void Player::Tick(float delta) {
  entityStateMachine->Tick(delta);
}

void Player::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  renderer.SetColor(0, 0, 0);
  Vector2 interpolatedPosition = GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());
  renderer.RenderFillRect(x, y, GetWidth(), GetHeight());
}

void Player::SetState(EntityStateID id) {
  entityStateMachine->Change(id);
}

}
