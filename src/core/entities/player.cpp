#include "player.h"
#include "movable_delegate.h"
#include "player_state_machine_impl.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

Player::Player(Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movableObject = MovableObjectDelegate::Create(200, 200);
  playerStateMachine = PlayerStateMachineImpl::Create(this);
}

Player_uptr Player::Create(Image_sptr sheet) {
  return std::make_unique<Player>(sheet);
}

void Player::Tick(float delta) {
  movableObject->Tick(delta);
  playerStateMachine->Tick(delta);
}

}
