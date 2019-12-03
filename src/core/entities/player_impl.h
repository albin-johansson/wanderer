#pragma once
#include "player.h"
#include "abstract_entity.h"
#include "player_state_machine.h"
#include "image.h"
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The Player class represents the entity that is controlled by the player.
 *
 * @see IEntity
 * @since 0.1.0
 */
class PlayerImpl final : public AbstractEntity, public IPlayer {
 private:
  IPlayerStateMachine_uptr playerStateMachine = nullptr;

 public:
  /**
   * @param sheet a shared pointer to the tile sheet image which will be used by the player.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  explicit PlayerImpl(Image_sptr sheet);

  ~PlayerImpl() override = default;

  void Tick(IWandererCore& core, float delta) override;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  void HandleInput(const Input& input, const IWandererCore& core) override {
    playerStateMachine->HandleInput(input, core);
  }

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override {
    playerStateMachine->Draw(renderer, viewport);
  }
};

}
