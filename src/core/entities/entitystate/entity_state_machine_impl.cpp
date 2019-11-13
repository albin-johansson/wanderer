#include "entity_state_machine_impl.h"
#include "objects.h"
#include "entity_moving_state.h"
#include "entity_idle_state.h"

namespace wanderer::core {

EntityStateMachineImpl::EntityStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::WALK, std::make_shared<EntityMovingState>(entity, this));
  Put(EntityStateID::IDLE, std::make_shared<EntityIdleState>(entity, this));

  Change(EntityStateID::IDLE);
}

EntityStateMachineImpl::~EntityStateMachineImpl() = default;

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
    currentState->ExitState();
  }

  auto next = states.at(id);
  next->EnterState();
  currentState = next;
}

void EntityStateMachineImpl::Tick(float delta) {
  if (currentState != nullptr) {
    currentState->Tick(delta);
  }
}

void EntityStateMachineImpl::Draw(visuals::Renderer& renderer,
                                  const Viewport& viewport) const noexcept {
  if (currentState != nullptr) {
    currentState->Draw(renderer, viewport);
  }
}

}
