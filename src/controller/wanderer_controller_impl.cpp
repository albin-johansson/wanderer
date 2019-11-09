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

  auto now = static_cast<double>(SDL_GetTicks());
  auto then = 0.0;
  auto delta = 0.0;
  auto accumulator = 0.0;

  while (running) {
    then = now;
    now = static_cast<double>(SDL_GetTicks());
    delta = (now - then) / 1000.0;

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