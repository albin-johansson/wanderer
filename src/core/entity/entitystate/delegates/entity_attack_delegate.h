#pragma once
#include "entity_state.h"

namespace wanderer {

class IEntityStateMachine;

/**
 * The EntityAttackDelegate class is an implementation of IEntityState that is
 * meant to be used for delegating idle entity attack calls.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class EntityAttackDelegate final : public IEntityState {
 public:
  /**
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityAttackDelegate(IEntityStateMachine* parent);

  ~EntityAttackDelegate() override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void tick(const IWandererCore& core, float delta) override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

 private:
  static constexpr int SOURCE_MELEE_Y = 768;
  static constexpr int SOURCE_MAGIC_Y = 0;
  static constexpr int MELEE_FRAMES = 6;
  static constexpr int MAGIC_FRAMES = 7;

  IEntityStateMachine* m_parent = nullptr;  // FIXME don't use raw pointers
};

}  // namespace wanderer
