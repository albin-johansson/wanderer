#include "player.h"
#include "movable_delegate.h"
#include "player_state_machine_impl.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

Player::Player(Image_sptr sheet, const IGame& game) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movableObject = MovableObjectDelegate::Create(200, 200);
  playerStateMachine = PlayerStateMachineImpl::Create(this);
  playerStateMachine->SetState(EntityStateID::IDLE, game);
}

Player_uptr Player::Create(Image_sptr sheet, const IGame& game) {
  return std::make_unique<Player>(std::move(sheet), game);
}

void Player::Tick(const IGame& game, float delta) {
  movableObject->Tick(game, delta);
  playerStateMachine->Tick(game, delta);
}

}
