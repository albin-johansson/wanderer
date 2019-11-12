#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "bad_state_exception.h"
#include "objects.h"
#include "input.h"

#include <iostream>

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core)
    : playerController(PlayerController(this)) {
  this->core = Objects::RequireNonNull(std::move(core));

  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
    throw BadStateException();
  }

  vsyncDelta = 1.0f / static_cast<float>(dm.refresh_rate);

  window = std::make_unique<Window>("Wanderer", dm.w, dm.h);
  window->SetFullscreen(false);

  this->core->SetViewportWidth(window->GetWidth());
  this->core->SetViewportHeight(window->GetHeight());

  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
  keyStateManager = std::make_shared<KeyStateManager>();
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::UpdateInput() {
  keyStateManager->Update();
  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_ESCAPE)) {
    Quit();
  }

  core->HandleInput(Input(keyStateManager));
}

void WandererControllerImpl::Run() {
  running = true;
  window->Show();

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 then = 0;

  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  float delta;
  float accumulator = 0;
  float deltaBuffer = 0; // this buffer keeps track of the extra bits of time

  while (running) {
    UpdateInput();

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

    while (accumulator >= IWandererCore::TIME_STEP) {
      accumulator -= IWandererCore::TIME_STEP;

      core->SavePositions(); // TODO force core to do this by itself
      core->Update();
      core->UpdateViewport();
    }

    float alpha = accumulator / IWandererCore::TIME_STEP;
    if (alpha > 1.0f) {
      alpha = 1.0f;
    }

    core->Interpolate(alpha);
    core->Render(*renderer);
  }

  window->Hide();
}

void WandererControllerImpl::Quit() {
  running = false;
}

void WandererControllerImpl::MovePlayer(Direction direction) {
  core->MovePlayer(direction);
}

void WandererControllerImpl::StopPlayer(Direction direction) {
  core->StopPlayer(direction);
}

}