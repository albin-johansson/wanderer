#include "smooth_fixed_timestep_loop.h"
#include "objects.h"
#include <SDL.h>
#include <iostream>

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(KeyStateManager_sptr keyStateManager,
                                                 float vsyncRate) : vsyncRate(vsyncRate) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  quit = false;
  now = SDL_GetPerformanceCounter();
  then = now;
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() = default;

void SmoothFixedTimestepLoop::UpdateInput(core::IWandererCore& core) {
  keyStateManager->Update();
  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_ESCAPE)) {
    quit = true;
  }

  core.HandleInput(Input(keyStateManager));
}

void SmoothFixedTimestepLoop::SmoothDelta() {
  static float deltaBuffer = 0;
  delta += deltaBuffer;

//  float frameCount = (delta * vsyncRate);
  int frameCount = (int) (delta * vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  const float oldDelta = delta;
  delta = static_cast<float>(frameCount) / vsyncRate;
  deltaBuffer = oldDelta - delta;
}

/* Reference for delta smoothing: https://frankforce.com/?p=2636 */
void SmoothFixedTimestepLoop::Update(IWandererCore& core, Renderer& renderer) {
  UpdateInput(core);

  then = now;
  now = SDL_GetPerformanceCounter();

  delta = static_cast<float>(now - then) / SDL_GetPerformanceFrequency();

  SmoothDelta();

  if (delta > MAX_FRAME_TIME) {
    delta = MAX_FRAME_TIME;
  }

  accumulator += delta;

  while (accumulator >= FIXED_TIME_STEP) {
    accumulator -= FIXED_TIME_STEP;
    core.Update(FIXED_TIME_STEP);
  }

  float alpha = accumulator / FIXED_TIME_STEP;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  core.Render(renderer, alpha);
}

}
