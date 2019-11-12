#pragma once
#include "entity_state.h"
#include "entity.h"

namespace wanderer::core {

class IEntityStateMachine;

class EntityMovingState final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;
  bool areMoveKeysDown = false;

  void CheckPressed(IEntity& entity, const Input& input);

  void CheckReleased(IEntity& entity, const Input& input);

 public:
  explicit EntityMovingState(IEntityStateMachine* parent);

  ~EntityMovingState() override;

  void Update(IEntity& entity, float delta) override;

  void HandleInput(IEntity& entity, const Input& input) override;

  void EnterState(IEntity& entity) override;

  void ExitState(IEntity& entity) override;
};

}
