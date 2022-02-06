#include "wanderer_game.hpp"

#include <algorithm>  // min

#include "wanderer/data/constants.hpp"
#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

constexpr auto window_flags = cen::window::hidden | cen::window::allow_high_dpi;

constexpr auto renderer_flags = cen::renderer::accelerated |      //
                                cen::renderer::target_textures |  //
                                cen::renderer::vsync;

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

wanderer_game::wanderer_game()
    : mLoopState{make_loop_state()}
    , mWindow{"Wanderer", cen::window::default_size(), window_flags}
    , mRenderer{mWindow.create_renderer(renderer_flags)}
{
  mRenderer.set_logical_size({logical_width, logical_height});
  mMouse.set_logical_size({logical_width_f, logical_height_f});

  log_debug("Game loop refresh rate is '{}'", mLoopState.rate);
  log_debug("Game loop fixed delta is '{}'", mLoopState.delta);
  log_debug("Maximum amount of ticks per frame is '{}'", mLoopState.max_ticks_per_frame);
}

void wanderer_game::run()
{
  mWindow.show();

  mLoopState.then = static_cast<float64>(cen::now());

  while (mRunning) {
    const auto newTime = static_cast<float64>(cen::now());
    auto frameTime = newTime - mLoopState.then;

    mLoopState.then = static_cast<float64>(newTime) / mLoopState.frequency;

    int steps = 0;
    while (frameTime > 0) {
      if (steps > mLoopState.max_ticks_per_frame) {
        break; /* Avoids spiral-of-death by limiting maximum amount of steps */
      }

      process_events();  // TODO should we process events here?
      if (!mRunning) {
        break;
      }

      const auto dt = std::min(frameTime, mLoopState.delta);
      update(static_cast<float32>(dt));

      frameTime -= dt;
      ++steps;
    }

    render();
  }

  mWindow.hide();
}

void wanderer_game::process_events()
{
  cen::event_handler handler;
  while (handler.poll()) {
    if (handler.is(cen::event_type::quit)) {
      mRunning = false;
      break;
    }
  }

  mKeyboard.refresh();
}

void wanderer_game::update(const float32 dt)
{
  mDispatcher.update();

  // TODO
}

void wanderer_game::render()
{
  mRenderer.clear_with(cen::colors::hot_pink);

  mRenderer.present();
}

}  // namespace wanderer