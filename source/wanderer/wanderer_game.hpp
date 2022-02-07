#pragma once

#include <centurion.hpp>
#include <entt/entt.hpp>

#include "common.hpp"
#include "core/game_loop.hpp"
#include "data/cfg.hpp"

namespace wanderer {

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
  game_cfg _cfg;

  cen::window _window;
  cen::renderer _renderer;
  cen::keyboard _keyboard;

  entt::registry _registry;
  entt::dispatcher _dispatcher;
};

}  // namespace wanderer
