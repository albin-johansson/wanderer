#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "input.h"
#include "time_utils.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(std::unique_ptr<KeyStateManager> ksm,
                                                 std::unique_ptr<MouseStateManager> msm,
                                                 float vsyncRate)
    : vsyncRate{vsyncRate},
      timeStep{1.0f / vsyncRate},
      counterFreq{static_cast<float>(TimeUtils::GetHighResFreq())} {
  input = std::make_unique<Input>(std::move(ksm), std::move(msm));
  now = TimeUtils::GetHighResTime();
  then = now;
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() = default;

void SmoothFixedTimestepLoop::UpdateInput(IWandererCore& core) {
  input->Update();

  if (input->WasQuitRequested() || input->WasReleased(SDL_SCANCODE_O)) {
    core.Quit();
  }

  core.HandleInput(*input);
}

void SmoothFixedTimestepLoop::SmoothDelta() {
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  delta += deltaBuffer;

  int frameCount = static_cast<int>(delta * vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  float oldDelta = delta;
  delta = static_cast<float>(frameCount) / vsyncRate;
  deltaBuffer = oldDelta - delta;
}

void SmoothFixedTimestepLoop::Update(IWandererCore& core, Renderer& renderer) {
  UpdateInput(core);

  then = now;
  now = TimeUtils::GetHighResTime();

  delta = static_cast<float>(now - then) / counterFreq;

  if (delta > MAX_FRAME_TIME) {
    delta = MAX_FRAME_TIME;
  }

  SmoothDelta();

  accumulator += delta;

  while (accumulator >= timeStep) {
    accumulator -= timeStep;
    core.Update(timeStep);
  }

  float alpha = accumulator / timeStep;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  renderer.SetColor(0, 0, 0);
  renderer.Clear();

  core.Render(renderer, alpha);

  renderer.Present();
}

}
