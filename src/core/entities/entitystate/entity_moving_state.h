#pragma once
#include "entity_state.h"
#include "entity.h"

namespace wanderer::core {

class IEntityStateMachine;

/**
 * The EntityMovingState class is an implementation of the IEntityState interface that represents
 * the state of a moving entity.
 *
 * @since 0.1.0
 */
class EntityMovingState final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;
  bool areMoveKeysDown = false;

  void CheckPressed(IEntity& entity, const Input& input);

  void CheckReleased(IEntity& entity, const Input& input);

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityMovingState(IEntityStateMachine* parent);

  ~EntityMovingState() override;

  void Update(IEntity& entity, float delta) override;

  void HandleInput(IEntity& entity, const Input& input) override;

  void EnterState(IEntity& entity) override;

  void ExitState(IEntity& entity) override;
};

}
