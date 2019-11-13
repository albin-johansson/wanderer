#include "player.h"
#include "movable_delegate.h"
#include "entity_state_machine_impl.h"
#include <memory>
#include "objects.h"

namespace wanderer::core {

Player::Player(visuals::Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movableObject = std::make_unique<MovableObjectDelegate>(200, 200);
  entityStateMachine = std::make_unique<EntityStateMachineImpl>(this);
}

void Player::HandleInput(const Input& input) {
  entityStateMachine->HandleInput(input);
}

void Player::Tick(float delta) {
  movableObject->Tick(delta);
  entityStateMachine->Tick(delta);
}

void Player::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  entityStateMachine->Draw(renderer, viewport);
//  renderer.SetColor(0, 0, 0);
//  Vector2 interpolatedPosition = GetInterpolatedPosition();
//  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
//  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());
//
//  auto src = Rectangle(0, 0, 64, 64);
//  auto dst = Rectangle(x, y, GetWidth(), GetHeight());
//  renderer.RenderTexture(sheet->GetTexture(), src, dst);
}

void Player::SetState(EntityStateID id) {
  entityStateMachine->Change(id);
}

}
