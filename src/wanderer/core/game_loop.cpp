#include "game_loop.hpp"

#include <algorithm>  // min

#include <centurion/system.hpp>
#include <centurion/video.hpp>
#include <spdlog/spdlog.h>

namespace wanderer {

GameLoop::GameLoop()
{
  const auto refresh_rate = cen::display_mode::desktop().refresh_rate().value();

  mState.rate = static_cast<float64>(std::min(120, refresh_rate));
  mState.fixed_dt = 1.0 / mState.rate;

  mState.frequency = static_cast<float64>(cen::frequency());
  mState.last_update = static_cast<float64>(cen::now());

  mState.max_ticks_per_frame = 5;

  spdlog::debug("[GameLoop] Refresh rate: {}", mState.rate);
  spdlog::debug("[GameLoop] Frequency: {}", mState.frequency);
  spdlog::debug("[GameLoop] Fixed delta: {}", mState.fixed_dt);
}

void GameLoop::start()
{
  mRunning = true;
  mState.last_update = now();

  // The following is a semi-fixed delta time game loop implementation.
  // Logic updates are detached from rendered frames, that is, there may be multiple logic
  // updates for each render call.
  while (mRunning) {
    const auto new_time = now();

    auto frame_time = new_time - mState.last_update;
    mState.last_update = new_time;

    int32 ticks = 0;
    while (frame_time > 0) {
      // Avoids spiral-of-death
      if (ticks > mState.max_ticks_per_frame) {
        break;
      }

      process_events();

      if (!mRunning) {
        break;
      }

      const auto dt = std::min(frame_time, mState.fixed_dt);
      update(static_cast<float32>(dt));

      frame_time -= dt;
      ++ticks;
    }

    render();
  }
}

void GameLoop::stop()
{
  mRunning = false;
}

auto GameLoop::now() const -> float64
{
  return static_cast<float64>(cen::now()) / mState.frequency;
}

}  // namespace wanderer