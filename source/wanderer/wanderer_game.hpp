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
class wanderer_game final : game_loop
{
 public:
  explicit wanderer_game(const game_cfg& cfg);

  void run();

 protected:
  void process_events() override;

  void update(float32 dt) override;

  void render() override;

 private:
  game_cfg mCfg;
  settings mSettings;

  graphics_ctx mGraphics;
  input_state mInput;

  entt::dispatcher mDispatcher;
  entt::registry mMainRegistry;

  void on_action(const action_event& event);

  void on_move_player(const move_player_event& event);

  void on_stop_player(const stop_player_event& event);

  [[nodiscard]] auto current_registry() -> entt::registry&;
};

}  // namespace wanderer
