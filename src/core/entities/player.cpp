#include "player.h"
#include "movable_delegate.h"
#include "player_state_machine_impl.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

Player::Player(Image_sptr sheet) : AbstractEntity(sheet) {
  playerStateMachine = PlayerStateMachineImpl::Create(this);
}

Player_uptr Player::Create(Image_sptr sheet) {
  return std::make_unique<Player>(std::move(sheet));
}

void Player::Tick(const IGame& game, float delta) {
  AbstractEntity::Tick(game, delta);
  playerStateMachine->Tick(game, delta);
}

}
