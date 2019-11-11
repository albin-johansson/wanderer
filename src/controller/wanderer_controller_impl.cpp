#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "bad_state_exception.h"
#include "objects.h"

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
//  SDL_Log("Width: %i", dm.w);
//  SDL_Log("Height: %i", dm.h);
//  SDL_Log("Refresh rate: %i", dm.refresh_rate);

  window = std::make_unique<Window>("Wanderer", dm.w, dm.h);
  window->SetFullscreen(true);

  this->core->SetViewportWidth(window->GetWidth());
  this->core->SetViewportHeight(window->GetHeight());

  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
  keyStateManager = std::make_unique<KeyStateManager>();
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::UpdateInput() {
  keyStateManager->Update();
  SDL_PumpEvents();

  if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0
      || keyStateManager->WasReleased(SDL_SCANCODE_ESCAPE)) {
    Quit();
  }

  playerController.Update(*keyStateManager);
}

void WandererControllerImpl::Run() {
  running = true;
  window->Show();

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 then = 0;

  float delta;
  float accumulator = 0.0f;

  while (running) {
    then = now;
    now = SDL_GetPerformanceCounter();

    auto diff = static_cast<float>(now - then);
    delta = diff / SDL_GetPerformanceFrequency();

    UpdateInput();

    if (delta > MAX_FRAME_TIME) {
      delta = MAX_FRAME_TIME;
    }

    accumulator += delta;

    while (accumulator >= IWandererCore::TIME_STEP) {
      core->SavePositions();
      core->Update();

      accumulator -= IWandererCore::TIME_STEP;
      core->Interpolate(accumulator / IWandererCore::TIME_STEP);
      core->UpdateViewport();
    }

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