#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"

namespace wanderer::core {

/**
 * The EntityAttackDelegate class is an implementation of IEntityState that is meant to be used for
 * delegating idle entity attack calls.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class EntityAttackDelegate final : public IEntityState {
 private:
  static constexpr int SOURCE_MELEE_Y = 768;
  static constexpr int SOURCE_MAGIC_Y = 0;
  static constexpr int MELEE_FRAMES = 6;
  static constexpr int MAGIC_FRAMES = 7;

  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;

 public:
  /**
   * @param entity a pointer to the associated entity instance.
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if any of the pointers are null.
   * @since 0.1.0
   */
  EntityAttackDelegate(IEntity* entity, IEntityStateMachine* parent);

  ~EntityAttackDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void Tick(const IGame& game, float delta) override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

};

}
