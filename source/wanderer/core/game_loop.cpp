#include "game_loop.hpp"

#include <algorithm>  // min

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_loop_state() -> loop_state
{
  const auto mode = cen::display_mode::desktop();

  loop_state state;

  state.rate = std::min(240.0, static_cast<float64>(mode.refresh_rate().value()));
  state.delta = 1.0 / state.rate;

  state.then = static_cast<float64>(cen::now());
  state.frequency = static_cast<float64>(cen::frequency());

  state.max_ticks_per_frame = 5;

  return state;
}

}  // namespace

game_loop::game_loop() : _state{make_loop_state()}
{
  log_debug("Game loop refresh rate is '{}'", _state.rate);
  log_debug("Game loop fixed delta is '{}'", _state.delta);
  log_debug("Maximum amount of ticks per frame is '{}'", _state.max_ticks_per_frame);
}

void game_loop::start()
{
  _running = true;
  _state.then = static_cast<float64>(cen::now());

  while (_running) {
    const auto newTime = static_cast<float64>(cen::now());
    auto frameTime = newTime - _state.then;

    _state.then = static_cast<float64>(newTime) / _state.frequency;

    int steps = 0;
    while (frameTime > 0) {
      /* Avoids spiral-of-death by limiting maximum amount of steps */
      if (steps > _state.max_ticks_per_frame) {
        break;
      }

      process_events();  // TODO should we process events here?

      if (!_running) {
        break;
      }

      const auto dt = std::min(frameTime, _state.delta);
      update(static_cast<float32>(dt));

      frameTime -= dt;
      ++steps;
    }

    render();
  }
}

void game_loop::stop()
{
  _running = false;
}

}  // namespace wanderer