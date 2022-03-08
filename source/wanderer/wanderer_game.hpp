#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/game_loop.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/fwd.hpp"
#include "wanderer/io/settings.hpp"

namespace wanderer {

/**
 * \brief The heart of the game.
 */
class WandererGame final : GameLoop
{
 public:
  explicit WandererGame(const GameConfig& cfg);

  void run();

 protected:
  void process_events() override;

  void update(float32 dt) override;

  void render() override;

 private:
  GameConfig mCfg;
  Settings mSettings;

  Graphics mGraphics;
  InputState mInput;

  entt::dispatcher mDispatcher;
  entt::registry mMainRegistry;

  void on_action(const ActionEvent& event);

  void on_move_player(const MovePlayerEvent& event);

  void on_stop_player(const StopPlayerEvent& event);

  [[nodiscard]] auto current_registry() -> entt::registry&;
};

}  // namespace wanderer
