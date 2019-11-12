#pragma once
#include "entity_state.h"

namespace wanderer::core {

class IEntityStateMachine;

class EntityIdleState : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  explicit EntityIdleState(IEntityStateMachine* parent);

  ~EntityIdleState() override;

  void Update(IEntity& entity, float delta) override;

  void HandleInput(IEntity& entity, const Input& input) override;

  void EnterState(IEntity& entity) override;

  void ExitState(IEntity& entity) override;

};

}
