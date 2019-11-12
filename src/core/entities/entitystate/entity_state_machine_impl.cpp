#include "entity_state_machine_impl.h"
#include "objects.h"
#include "entity_moving_state.h"
#include "entity_idle_state.h"

namespace wanderer::core {

EntityStateMachineImpl::EntityStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::WALK, std::make_shared<EntityMovingState>(this));
  Put(EntityStateID::IDLE, std::make_shared<EntityIdleState>(this));

  Change(EntityStateID::IDLE);
}

EntityStateMachineImpl::~EntityStateMachineImpl() = default;

void EntityStateMachineImpl::Put(EntityStateID id, IEntityState_sptr state) {
  states.insert(std::pair<EntityStateID, IEntityState_sptr>(id, state));
}

void EntityStateMachineImpl::HandleInput(const Input& input) {
  if (currentState != nullptr) {
    currentState->HandleInput(*entity, input);
  }
}

void EntityStateMachineImpl::Change(EntityStateID id) {
  if (currentState != nullptr) {
    currentState->ExitState(*entity);
  }

  auto next = states.at(id);
  next->EnterState(*entity);
  currentState = next;
}

void EntityStateMachineImpl::Tick(float delta) {
  if (currentState != nullptr) {
    currentState->Update(*entity, delta);
  }
}

}
