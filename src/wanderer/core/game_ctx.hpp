#pragma once

#include <centurion/keyboard.hpp>
#include <centurion/mouse.hpp>
#include <entt/signal/dispatcher.hpp>

namespace wanderer {

struct GameCtx final {
  cen::mouse mouse;
  cen::keyboard keyboard;
  entt::dispatcher dispatcher;
};

}  // namespace wanderer
