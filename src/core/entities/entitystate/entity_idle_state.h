#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_draw_delegate.h"

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
  IEntity* entity = nullptr;
  EntityDrawDelegate drawDelegate;

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityIdleState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityIdleState() override;

  void Tick(float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  void HandleInput(const Input& input) override;

  void Enter() override;

  void Exit() override;

};

}
