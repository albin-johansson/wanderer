#pragma once
#include "player.h"
#include "abstract_entity.h"
#include "player_state_machine.h"
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The Player class is an implementation of the IPlayer interface, the class also extends the
 * AbstractEntity class.
 *
 * @see AbstractEntity
 * @see IEntity
 * @since 0.1.0
 */
class PlayerImpl final : public AbstractEntity, public IPlayer {
 private:
  std::unique_ptr<IPlayerStateMachine> playerStateMachine = nullptr;

  void Init();

 public:
  /**
   * @param sheet a pointer to the tile sheet image which will be used by the player.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  explicit PlayerImpl(const std::shared_ptr<centurion::Image>& sheet);

  ~PlayerImpl() override;

  void tick(IWandererCore& core, float delta) override;

  void handle_input(const Input& input, const IWandererCore& core) override;

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const noexcept override;
};

}
