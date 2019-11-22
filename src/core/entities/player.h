#pragma once
#include "abstract_entity.h"
#include "player_state_machine.h"
#include "image.h"
#include <memory>

namespace wanderer::core {

class Player;

using Player_uptr = std::unique_ptr<Player>;
using Player_sptr = std::shared_ptr<Player>;
using Player_wptr = std::weak_ptr<Player>;

/**
 * The Player class represents the entity that is controlled by the player.
 *
 * @see IEntity
 * @since 0.1.0
 */
class Player final : public AbstractEntity {
 private:
  IPlayerStateMachine_uptr playerStateMachine = nullptr;

 public:
  /**
   * @param sheet a shared pointer to the tile sheet image which will be used by the player.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  explicit Player(visuals::Image_sptr sheet);

  ~Player() override = default;

  /**
   * Creates and returns a unique pointer to a player instance.
   *
   * @param sheet a shared pointer to the tile sheet image which will be used by the player.
   * @return a unique pointer to a player instance.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  static Player_uptr Create(visuals::Image_sptr sheet);

  void Tick(const IGame& game, float delta) override;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  void HandleInput(const Input& input, const IGame& game) {
    playerStateMachine->HandleInput(input, game);
  }

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override {
    playerStateMachine->Draw(renderer, viewport);
  }
};

}
