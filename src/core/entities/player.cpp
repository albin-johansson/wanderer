#include "player.h"
#include "movable_delegate.h"
#include "entity_state_machine_impl.h"
#include <memory>
#include "objects.h"

namespace wanderer::core {

Player::Player(visuals::Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movableObject = MovableObjectDelegate::Create(200, 200);
  entityStateMachine = EntityStateMachineImpl::Create(this);
}

Player_uptr Player::Create(visuals::Image_sptr sheet) {
  return std::make_unique<Player>(sheet);
}

void Player::HandleInput(const Input& input) {
  entityStateMachine->HandleInput(input);
}

void Player::Tick(float delta) {
  movableObject->Tick(delta);
  entityStateMachine->Tick(delta);
}

void Player::Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept {
  entityStateMachine->Draw(renderer, viewport);
}

void Player::SetState(EntityStateID id) {
  entityStateMachine->Change(id);
}

}
