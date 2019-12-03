#include "player_impl.h"
#include "movable_delegate.h"
#include "player_state_machine_impl.h"

namespace albinjohansson::wanderer {

PlayerImpl::PlayerImpl(Image_sptr sheet) : AbstractEntity(std::move(sheet)) {
  playerStateMachine = PlayerStateMachineImpl::Create(static_cast<IEntity*>(this));
}

void PlayerImpl::Tick(IWandererCore& core, float delta) {
  AbstractEntity::Tick(core, delta);
  playerStateMachine->Tick(core, delta);
}

}
