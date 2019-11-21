#include "skeleton_state_machine.h"
#include "objects.h"
#include "skeleton_idle_state.h"
#include "skeleton_moving_state.h"
#include "skeleton_attack_state.h"

namespace wanderer::core {

SkeletonStateMachine::SkeletonStateMachine(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  // TODO add different states
  Put(EntityStateID::IDLE, std::make_unique<SkeletonIdleState>(this));
  Put(EntityStateID::WALK, std::make_unique<SkeletonMovingState>(this));
  Put(EntityStateID::ATTACK, std::make_unique<SkeletonAttackState>(this));

  activeStateID = EntityStateID::IDLE;
}

SkeletonStateMachine::~SkeletonStateMachine() = default;

void SkeletonStateMachine::Put(EntityStateID id, IEntityState_uptr state) {
  states.insert(std::pair<EntityStateID, std::unique_ptr<IEntityState>>(id, std::move(state)));
}

void SkeletonStateMachine::Tick(const IGame& game, float delta) {
  states.at(activeStateID)->Tick(game, delta);
}

void SkeletonStateMachine::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  states.at(activeStateID)->Draw(renderer, viewport);
}

void SkeletonStateMachine::SetState(EntityStateID id, const IGame& game) {
  states.at(activeStateID)->Exit(game);
  activeStateID = id;
  states.at(activeStateID)->Enter(game);
}

IEntity& SkeletonStateMachine::GetEntity() {
  return *entity;
}

}
