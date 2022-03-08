#include "game_loop.hpp"

#include <algorithm>  // min

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_loop_state() -> LoopState
{
  const auto display = cen::display_mode::desktop();

  LoopState state;

  state.rate = std::min(120.0, static_cast<float64>(display.refresh_rate().value()));
  state.fixed_dt = 1.0 / state.rate;

  state.frequency = static_cast<float64>(cen::frequency());
  state.then = static_cast<float64>(cen::now()) / state.frequency;

  state.max_ticks_per_frame = 5;

  return state;
}

}  // namespace

GameLoop::GameLoop() : _state{make_loop_state()}
{
  debug("Game loop refresh rate is '{}'", _state.rate);
  debug("Game loop fixed delta is '{}'", _state.fixed_dt);
  debug("Maximum amount of ticks per frame is '{}'", _state.max_ticks_per_frame);
}

void GameLoop::start()
{
  const auto now = [this]() noexcept {
    return static_cast<float64>(cen::now()) / _state.frequency;
  };

  _running = true;
  _state.then = now();

  while (_running) {
    const auto newTime = now();
    auto frameTime = newTime - _state.then;
    _state.then = newTime;

    int32 steps = 0;
    while (frameTime > 0) {
      /* Avoids spiral-of-death by limiting maximum amount of steps */
      if (steps > _state.max_ticks_per_frame) {
        break;
      }

      process_events();

      if (!_running) {
        break;
      }

      const auto dt = std::min(frameTime, _state.fixed_dt);
      update(static_cast<float32>(dt));

      frameTime -= dt;
      ++steps;
    }

    render();
  }
}

void GameLoop::stop()
{
  _running = false;
}

}  // namespace wanderer