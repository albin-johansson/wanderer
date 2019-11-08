#include "wanderer_controller_impl.h"
#include <SDL.h>

using namespace wanderer::core;
using namespace wanderer::view;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(core::IWandererCore_uptr core) {
  this->core = std::move(core); // TODO null check
  window = std::make_unique<Window>("Wanderer", 1500, 800);
  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::UpdateLoop(float delta) {
  if (delta > MAX_FRAME_TIME) {
    delta = MAX_FRAME_TIME;
  }

  HandleInput();

  accumulator += delta;

  while (accumulator >= IWandererCore::TIME_STEP) {
    core->SavePositions();

    core->Update();
    accumulator -= IWandererCore::TIME_STEP;
  }

  core->Interpolate(accumulator / IWandererCore::TIME_STEP);
  core->Render(*renderer);
}

void WandererControllerImpl::HandleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      Quit();
    }
  }
}

void WandererControllerImpl::Run() {
  running = true;
  Uint32 now = 0;
  Uint32 last = 0;

  window->Show();

  while (running) {
    last = now;
    now = SDL_GetTicks();

    float delta = static_cast<float>(now - last) / 1000.0f;

    UpdateLoop(delta);
  }
}

void WandererControllerImpl::Quit() {
  running = false;
}

}