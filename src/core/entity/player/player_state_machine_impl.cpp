#include "player_state_machine_impl.h"

#include "entity.h"
#include "player_attack_state.h"
#include "player_dying_state.h"
#include "player_idle_state.h"
#include "player_moving_state.h"

namespace wanderer {

PlayerStateMachineImpl::PlayerStateMachineImpl(IEntity* entity)
    : AbstractEntityStateMachine(entity)
{
  put(EntityStateID::Idle, std::make_unique<PlayerIdleState>(this));
  put(EntityStateID::Die, std::make_unique<PlayerDyingState>(entity));
  put(EntityStateID::Walk, std::make_unique<PlayerMovingState>(this));
  put(EntityStateID::Attack, std::make_unique<PlayerAttackState>(this));
}

PlayerStateMachineImpl::~PlayerStateMachineImpl() = default;

void PlayerStateMachineImpl::HandleInput(const Input& input,
                                         const IWandererCore& core)
{
  get_active_state().handle_input(input, core);
}

}  // namespace wanderer
