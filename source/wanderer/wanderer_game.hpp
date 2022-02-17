#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/game_loop.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/fwd.hpp"
#include "wanderer/ui/menu_manager.hpp"

namespace wanderer {

/**
 * \brief The heart of the game.
 */
class wanderer_game final : game_loop
{
 public:
  wanderer_game();

  void run();

 protected:
  void process_events() override;

  void update(float32 dt) override;

  void render() override;

 private:
  game_cfg mCfg;

  graphics_ctx mGraphics;
  input_state mInput;

  menu_manager mMenus;

  entt::dispatcher mDispatcher;
  entt::registry mSharedRegistry;

  void on_action(const action_event& event);

  [[nodiscard]] auto current_registry() -> entt::registry&;
};

}  // namespace wanderer
