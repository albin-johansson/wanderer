#include "player_state_machine_impl.h"
#include "objects.h"
#include "player_moving_state.h"
#include "player_idle_state.h"
#include "player_attack_state.h"
#include "player_dying_state.h"

using namespace wanderer::visuals;

namespace wanderer::core {

PlayerStateMachineImpl::PlayerStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::IDLE, std::make_unique<PlayerIdleState>(entity, this));
  Put(EntityStateID::DIE, std::make_unique<PlayerDyingState>(entity, this));
  Put(EntityStateID::WALK, std::make_unique<PlayerMovingState>(entity, this));
  Put(EntityStateID::ATTACK, std::make_unique<PlayerAttackState>(entity, this));

  activeStateID = EntityStateID::IDLE;
  SetState(activeStateID);
}

PlayerStateMachineImpl::~PlayerStateMachineImpl() = default;

IPlayerStateMachine_uptr PlayerStateMachineImpl::Create(IEntity* entity) {
  return std::make_unique<PlayerStateMachineImpl>(entity);
}

void PlayerStateMachineImpl::Put(EntityStateID id, IPlayerState_uptr state) {
  states.insert(std::pair<EntityStateID, IPlayerState_uptr>(id, std::move(state)));
}

void PlayerStateMachineImpl::HandleInput(const Input& input) {
  states.at(activeStateID)->HandleInput(input);
}

void PlayerStateMachineImpl::SetState(EntityStateID id) {
  states.at(activeStateID)->Exit();

  activeStateID = id;
  states.at(activeStateID)->Enter();
}

void PlayerStateMachineImpl::Tick(float delta) {
  states.at(activeStateID)->Tick(delta);
}

void PlayerStateMachineImpl::Draw(Renderer& renderer, const Viewport& viewport) noexcept {
  states.at(activeStateID)->Draw(renderer, viewport);
}

}
