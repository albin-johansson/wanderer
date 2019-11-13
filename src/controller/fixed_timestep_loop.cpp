#include "fixed_timestep_loop.h"
#include "objects.h"
#include <SDL.h>

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

FixedTimestepLoop::FixedTimestepLoop(KeyStateManager_sptr keyStateManager, float vsyncDelta)
    : vsyncDelta(vsyncDelta) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  quit = false;
  now = SDL_GetPerformanceCounter();
  then = now;
}

FixedTimestepLoop::~FixedTimestepLoop() = default;

void FixedTimestepLoop::UpdateInput(core::IWandererCore& core) {
  keyStateManager->Update();
  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_ESCAPE)) {
    quit = true;
  }

  core.HandleInput(Input(keyStateManager));
}

/* Reference for delta smoothing: https://frankforce.com/?p=2636 */
void FixedTimestepLoop::Update(IWandererCore& core, Renderer& renderer) {
  UpdateInput(core);

  then = now;
  now = SDL_GetPerformanceCounter();
  delta = static_cast<float>(now - then) / SDL_GetPerformanceFrequency();

  delta += deltaBuffer;           // add in whatever time we currently have saved in the buffer
  const float oldDelta = delta;

  delta = vsyncDelta;             // use refresh rate as delta
  deltaBuffer = oldDelta - delta; // update delta buffer so we keep the same time on average

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
