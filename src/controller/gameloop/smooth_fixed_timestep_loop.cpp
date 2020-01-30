#include "smooth_fixed_timestep_loop.h"
#include <SDL.h>
#include <renderer.h>
#include <timer.h>
#include "wanderer_core.h"
#include "input.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(unique<KeyState> keyState,
                                                 unique<MouseState> mouseState,
                                                 float vsyncRate)
    : vsyncRate{vsyncRate},
      timeStep{1.0f / vsyncRate},
      counterFreq{static_cast<float>(Timer::high_res_freq())} {
  input = std::make_unique<Input>(std::move(keyState), std::move(mouseState));
  now = Timer::high_res();
  then = now;
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() = default;

void SmoothFixedTimestepLoop::update_input(IWandererCore& core) {
  input->update();

  if (input->was_quit_requested() || input->was_released(SDL_SCANCODE_O)) {
    core.quit();
  }

  core.handle_input(*input);
}

void SmoothFixedTimestepLoop::smooth_delta() {
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  delta += deltaBuffer;

  int frameCount = static_cast<int>(delta * vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  const float oldDelta = delta;
  delta = static_cast<float>(frameCount) / vsyncRate;
  deltaBuffer = oldDelta - delta;
}

void SmoothFixedTimestepLoop::update(IWandererCore& core, Renderer& renderer) {
  update_input(core);

  then = now;
  now = Timer::high_res();

  delta = static_cast<float>(now - then) / counterFreq;

  if (delta > maxFrameTime) {
    delta = maxFrameTime;
  }

  smooth_delta();

  accumulator += delta;

  while (accumulator >= timeStep) {
    accumulator -= timeStep;
    core.update(timeStep);
  }

  float alpha = accumulator / timeStep;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  renderer.set_color(0, 0, 0);
  renderer.clear();

  core.render(renderer, alpha);

  renderer.present();
}

}
