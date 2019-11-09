#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "objects.h"

using namespace wanderer::core;
using namespace wanderer::view;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core)
    : playerController(PlayerController(this)) {
  this->core = Objects::RequireNonNull(std::move(core));

  // FIXME avoid hardcoded window size
  window = std::make_unique<Window>("Wanderer", 1500, 800);
  window->SetFullscreen(false);

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

  Uint32 now = SDL_GetTicks();
  Uint32 then = 0;
  double delta = 0;
  double accumulator = 0;
  double timeStep = IWandererCore::TIME_STEP;

  while (running) {
    then = now;
    now = static_cast<double>(SDL_GetTicks());
    auto ms = now - then;
    delta = static_cast<double >(ms / 1000.0);

    UpdateInput();

    if (delta > MAX_FRAME_TIME) {
      delta = MAX_FRAME_TIME;
    }

    accumulator += delta;

    while (accumulator >= timeStep) {
      core->SavePositions();
      core->Update();

      accumulator -= timeStep;
      core->Interpolate(accumulator / timeStep);
    }

    core->Render(*renderer);

    if (delta < MIN_FRAME_TIME) {
      SDL_Delay(1);
    }
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