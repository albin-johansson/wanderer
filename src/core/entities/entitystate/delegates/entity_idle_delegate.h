#pragma once
#include "entity_state.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

/**
 * The EntityIdleDelegate class is an implementation of IEntityState that is
 * meant to be used for delegating idle entity state calls.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class EntityIdleDelegate final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  /**
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityIdleDelegate(IEntityStateMachine* parent);

  ~EntityIdleDelegate() override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

  void tick(const IWandererCore& core, float delta) override;

  /**
   * Returns a reference to the associated entity state machine.
   *
   * @return a reference to the associated entity state machine.
   * @since 0.1.0
   */
  [[nodiscard]] IEntityStateMachine& get_parent() noexcept;
};

}  // namespace albinjohansson::wanderer
