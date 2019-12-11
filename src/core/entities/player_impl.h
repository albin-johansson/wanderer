#pragma once
#include "player.h"
#include "abstract_entity.h"
#include "player_state_machine.h" // FIXME shouldn't be required, but is seems to be
#include <memory>

namespace albinjohansson::wanderer {

class IPlayerStateMachine;

/**
 * The Player class represents the entity that is controlled by the player.
 *
 * @see IEntity
 * @since 0.1.0
 */
class PlayerImpl final : public AbstractEntity, public IPlayer {
 private:
  std::unique_ptr<IPlayerStateMachine> playerStateMachine = nullptr;

 public:
  /**
   * @param sheet a pointer to the tile sheet image which will be used by the player.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  explicit PlayerImpl(std::shared_ptr<Image> sheet);

  ~PlayerImpl() override = default;

  void Tick(IWandererCore& core, float delta) override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;
};

}
