#include "entity_state_machine_impl.h"
#include "objects.h"
#include "entity_moving_state.h"
#include "entity_idle_state.h"
#include "entity_attack_state.h"
#include "entity_dying_state.h"

namespace wanderer::core {

EntityStateMachineImpl::EntityStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::WALK, std::make_shared<EntityMovingState>(entity, this));
  Put(EntityStateID::IDLE, std::make_shared<EntityIdleState>(entity, this));
  Put(EntityStateID::ATTACK, std::make_shared<EntityAttackState>(entity, this));
  Put(EntityStateID::DIE, std::make_shared<EntityDyingState>(entity, this));

  Change(EntityStateID::IDLE);
}

EntityStateMachineImpl::~EntityStateMachineImpl() = default;

IEntityStateMachine_uptr EntityStateMachineImpl::CreateUnique(IEntity* entity) {
  return std::make_unique<EntityStateMachineImpl>(entity);
}

void EntityStateMachineImpl::Put(EntityStateID id, IEntityState_sptr state) {
  states.insert(std::pair<EntityStateID, IEntityState_sptr>(id, state));
}

void EntityStateMachineImpl::HandleInput(const Input& input) {
  if (currentState != nullptr) {
    currentState->HandleInput(input);
  }
}

void EntityStateMachineImpl::Change(EntityStateID id) {
  if (currentState != nullptr) {
    currentState->Exit();
  }

  auto next = states.at(id);
  next->Enter();
  currentState = next;
}

void EntityStateMachineImpl::Tick(float delta) {
  if (currentState != nullptr) {
    currentState->Tick(delta);
  }
}

void EntityStateMachineImpl::Draw(visuals::Renderer& renderer,
                                  const Viewport& viewport) noexcept {
  if (currentState != nullptr) {
    currentState->Draw(renderer, viewport);
  }
}

}
