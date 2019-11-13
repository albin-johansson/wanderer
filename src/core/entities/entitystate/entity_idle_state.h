#pragma once
#include "entity_state.h"

namespace wanderer::core {

class IEntityStateMachine;

/**
 * The EntityIdleState class is an implementation of the IEntityState interface that represents
 * the state of an idle entity.
 *
 * @since 0.1.0
 */
class EntityIdleState final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityIdleState(IEntityStateMachine* parent);

  ~EntityIdleState() override;

  void Update(IEntity& entity, float delta) override;

  void HandleInput(IEntity& entity, const Input& input) override;

  void EnterState(IEntity& entity) override;

  void ExitState(IEntity& entity) override;

};

}
