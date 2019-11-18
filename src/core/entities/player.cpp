#include "player.h"
#include "movable_delegate.h"
#include "player_state_machine_impl.h"
#include <memory>
#include "objects.h"

namespace wanderer::core {

Player::Player(visuals::Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movableObject = MovableObjectDelegate::Create(200, 200);
  playerStateMachine = PlayerStateMachineImpl::Create(this);
}

Player_uptr Player::Create(visuals::Image_sptr sheet) {
  return std::make_unique<Player>(sheet);
}

//void Player::HandleInput(const Input& input) {
//  playerStateMachine->HandleInput(input);
//}

void Player::Tick(float delta) {
  movableObject->Tick(delta);
  playerStateMachine->Tick(delta);
}

//void Player::Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept {
//  playerStateMachine->Draw(renderer, viewport);
//}
//
//void Player::SetState(EntityStateID id) {
//  playerStateMachine->Change(id);
//}

}
