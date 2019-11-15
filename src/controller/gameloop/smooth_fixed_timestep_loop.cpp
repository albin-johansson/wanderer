#include "smooth_fixed_timestep_loop.h"
#include "objects.h"
#include "menu_state_machine_impl.h"
#include <SDL.h>
#include <iostream>

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(KeyStateManager_sptr keyStateManager,
                                                 MouseStateManager_sptr mouseStateManager,
                                                 float vsyncRate)
    : vsyncRate(vsyncRate), timeStep(1.0f / vsyncRate), counterFreq(SDL_GetPerformanceFrequency()) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  this->mouseStateManager = Objects::RequireNonNull(std::move(mouseStateManager));
  quit = false;
  now = SDL_GetPerformanceCounter();
  then = now;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                 SDL_LOG_PRIORITY_INFO,
                 "Using fixed timestep loop with delta time smoothing.");

  menuStateMachine = new MenuStateMachineImpl();
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() {
  delete menuStateMachine;
}

SmoothFixedTimestepLoop_uptr SmoothFixedTimestepLoop::CreateUnique(KeyStateManager_sptr keyStateManager,
                                                                   MouseStateManager_sptr mouseStateManager,
                                                                   float vsyncRate) {
  return std::make_unique<SmoothFixedTimestepLoop>(keyStateManager, mouseStateManager, vsyncRate);
}

void SmoothFixedTimestepLoop::UpdateInput(core::IWandererCore& core) {
  mouseStateManager->Update();
  keyStateManager->Update();

  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_O)) {
    quit = true;
  }

  auto input = Input(keyStateManager, mouseStateManager);
  menuStateMachine->HandleInput(input);

  if (!menuStateMachine->IsActiveMenuBlocking()) {
    core.HandleInput(input);
  }
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
    if (!menuStateMachine->IsActiveMenuBlocking()) {
      core.Update(timeStep);
    }
  }

  float alpha = accumulator / timeStep;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  renderer.SetColor(0, 0, 0);
  renderer.Clear();

  core.Render(renderer, alpha);
  menuStateMachine->Draw(renderer, core.GetViewport());

  renderer.Present();
}

}
