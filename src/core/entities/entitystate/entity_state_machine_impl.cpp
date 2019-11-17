#include "entity_state_machine_impl.h"
#include "objects.h"
#include "entity_moving_state.h"
#include "entity_idle_state.h"
#include "entity_attack_state.h"
#include "entity_dying_state.h"

using namespace wanderer::visuals;

namespace wanderer::core {

EntityStateMachineImpl::EntityStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::WALK, std::make_unique<EntityMovingState>(entity, this));
  Put(EntityStateID::IDLE, std::make_unique<EntityIdleState>(entity, this));
  Put(EntityStateID::ATTACK, std::make_unique<EntityAttackState>(entity, this));
  Put(EntityStateID::DIE, std::make_unique<EntityDyingState>(entity, this));

  activeStateID = EntityStateID::IDLE;
  Change(activeStateID);
}

EntityStateMachineImpl::~EntityStateMachineImpl() = default;

IEntityStateMachine_uptr EntityStateMachineImpl::Create(IEntity* entity) {
  return std::make_unique<EntityStateMachineImpl>(entity);
}

void EntityStateMachineImpl::Put(EntityStateID id, IEntityState_uptr state) {
  states.insert(std::pair<EntityStateID, IEntityState_uptr>(id, std::move(state)));
}

void EntityStateMachineImpl::HandleInput(const Input& input) {
  states.at(activeStateID)->HandleInput(input);
}

void EntityStateMachineImpl::Change(EntityStateID id) {
  states.at(activeStateID)->Exit();

  activeStateID = id;
  states.at(activeStateID)->Enter();
}

void EntityStateMachineImpl::Tick(float delta) {
  states.at(activeStateID)->Tick(delta);
}

void EntityStateMachineImpl::Draw(Renderer& renderer, const Viewport& viewport) noexcept {
  states.at(activeStateID)->Draw(renderer, viewport);
}

}
