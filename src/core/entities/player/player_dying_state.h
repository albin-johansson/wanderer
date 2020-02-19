#pragma once
#include "entity_dying_delegate.h"
#include "player_state.h"

namespace albinjohansson::wanderer {

class IEntity;

/**
 * The PlayerDyingState class is an implementation of the IPlayerState interface
 * that represents the state of the player when dying.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerDyingState final : public IPlayerState {
 private:
  EntityDyingDelegate dyingDelegate;

 public:
  /**
   * @param entity a pointer to the associated entity.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerDyingState(IEntity* entity);

  ~PlayerDyingState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void draw(const centurion::video::Renderer& renderer,
            const Viewport& viewport) const override;

  void tick(const IWandererCore& core, float delta) override;

  void enter(const IWandererCore& core) override;

  // TODO game over stuff
  void exit(const IWandererCore& core) override;
};

}  // namespace albinjohansson::wanderer
