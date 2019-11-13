#include "smooth_fixed_timestep_loop.h"
#include "objects.h"
#include <SDL.h>

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(KeyStateManager_sptr keyStateManager,
                                                 float vsyncDelta) : vsyncDelta(vsyncDelta) {
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

/* Reference for delta smoothing: https://frankforce.com/?p=2636 */
void SmoothFixedTimestepLoop::Update(IWandererCore& core, Renderer& renderer) {
  UpdateInput(core);

//  then = now;
//  now = SDL_GetPerformanceCounter();
//  delta = static_cast<float>(now - then) / SDL_GetPerformanceFrequency();

  delta += deltaBuffer;
  const float oldDelta = delta;

  delta = vsyncDelta;
  deltaBuffer = oldDelta - delta;

  if (delta > MAX_FRAME_TIME) {
    delta = MAX_FRAME_TIME;
  }

  accumulator += delta;

  while (accumulator >= delta) {
    accumulator -= delta;
    core.Update(delta);
  }

  float alpha = accumulator / delta;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  core.Interpolate(alpha);
  core.Render(renderer);
}

}
