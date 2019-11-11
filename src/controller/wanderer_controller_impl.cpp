#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "objects.h"

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core)
    : playerController(PlayerController(this)) {
  this->core = Objects::RequireNonNull(std::move(core));

  // FIXME avoid hardcoded window size
  window = std::make_unique<Window>("Wanderer", 1500, 800);
  window->SetFullscreen(false);

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

  double delta;
  double accumulator = 0.0;

  while (running) {
    then = now;
    now = SDL_GetPerformanceCounter();

    auto diff = static_cast<double>(now - then);
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
    }

    core->Render(*renderer);
  }

  window->Hide();
}

void WandererControllerImpl::Quit() {
  running = false;
}

void WandererControllerImpl::MovePlayer(core::Direction direction) {
  core->MovePlayer(direction);
}

void WandererControllerImpl::StopPlayer(core::Direction direction) {
  core->StopPlayer(direction);
}

}