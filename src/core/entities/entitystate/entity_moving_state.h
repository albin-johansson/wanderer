#pragma once
#include "abstract_entity_state.h"
#include "entity_state_machine.h"
#include "entity.h"

namespace wanderer::core {

/**
 * The EntityMovingState class is an implementation of the IEntityState interface that represents
 * the state of a moving entity.
 *
 * @since 0.1.0
 */
class EntityMovingState final : public AbstractEntityState {
 private:
  bool areMoveKeysDown = false;

  void CheckPressed(const Input& input);

  void CheckReleased(const Input& input);

 public:
  /**
   * @param entity a pointer to the associated entity instance.
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if any pointers are pointer null.
   * @since 0.1.0
   */
  EntityMovingState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityMovingState() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  void HandleInput(const Input& input) override;

  void Tick(float delta) override;

  void Enter() override;

  void Exit() override;
};

}
