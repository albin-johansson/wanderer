#pragma once

#include <centurion.hpp>
#include <entt/entt.hpp>

#include "common.hpp"

namespace wanderer {

struct loop_state final
{
  float64 rate{};               ///< Refresh rate (in Hz).
  float64 delta{};              ///< Fixed delta time.
  float64 then{};               ///< Time of last update.
  float64 frequency{};          ///< The frequency of the system counter.
  int32 max_ticks_per_frame{};  ///< Maximum amount of ticks per frame.
};

class wanderer_game final
{
 public:
  wanderer_game();

  void run();

 private:
  loop_state mLoopState;

  cen::window mWindow;
  cen::renderer mRenderer;
  cen::keyboard mKeyboard;
  cen::mouse mMouse;

  entt::registry mSharedRegistry;
  entt::dispatcher mDispatcher;

  bool mRunning{true};

  void process_events();

  void update(float32 dt);

  void render();
};

}  // namespace wanderer
