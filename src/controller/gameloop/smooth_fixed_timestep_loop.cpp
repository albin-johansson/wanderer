#include "smooth_fixed_timestep_loop.h"

#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"

#include "objects.h"
#include "input.h"
#include <SDL.h>
#include <iostream>

namespace albinjohansson::wanderer {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(std::shared_ptr<KeyStateManager> keyStateManager,
                                                 std::shared_ptr<MouseStateManager> mouseStateManager,
                                                 float vsyncRate)
    : vsyncRate(vsyncRate), timeStep(1.0f / vsyncRate), counterFreq(SDL_GetPerformanceFrequency()) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  this->mouseStateManager = Objects::RequireNonNull(std::move(mouseStateManager));

  now = SDL_GetPerformanceCounter();
  then = now;
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() = default;

void SmoothFixedTimestepLoop::UpdateInput(IWandererCore& core) {
  mouseStateManager->Update();
  keyStateManager->Update();

  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_O)) {
    core.Quit();
  }

  auto input = Input(keyStateManager, mouseStateManager);
  core.HandleInput(input);
}

void SmoothFixedTimestepLoop::SmoothDelta() {
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  static float deltaBuffer = 0;
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
  now = SDL_GetPerformanceCounter();

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
