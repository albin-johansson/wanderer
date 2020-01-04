#pragma once
#include "entity_state.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

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

  IEntityStateMachine* parent = nullptr;

 public:
  /**
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityAttackDelegate(IEntityStateMachine* parent);

  ~EntityAttackDelegate() override;

  void Draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

  void Tick(const IWandererCore& core, float delta) override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}
