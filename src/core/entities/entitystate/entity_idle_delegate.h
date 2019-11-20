#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"

namespace wanderer::core {

/**
 * The EntityIdleDelegate class is an implementation of IEntityState that is meant to be used for
 * delegating idle entity state calls.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class EntityIdleDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;

 public:
  /**
   * @param entity a pointer to the associated entity instance.
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  EntityIdleDelegate(IEntity* entity, IEntityStateMachine* parent);

  ~EntityIdleDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

  void Tick(const IGame& game, float delta) override;

  /**
   * Returns a pointer to the associated entity instance.
   *
   * @return a pointer to the associated entity instance.
   * @since 0.1.0
   */
  [[nodiscard]] inline IEntityStateMachine* GetParent() noexcept { return parent; }
};

}
