#include "wanderer_controller_impl.h"
#include <SDL.h>
#include "objects.h"
#include <iostream>

using namespace wanderer::core;
using namespace wanderer::view;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core) {
  this->core = Objects::RequireNonNull(std::move(core));

  // FIXME avoid hardcoded window size
  window = std::make_unique<Window>("Wanderer", 1920, 1080);
  window->SetFullscreen(true);

  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::HandleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
      Quit();
    }
  }
}

void WandererControllerImpl::Run() {
  running = true;
  window->Show();

  Uint32 now = SDL_GetTicks();
  Uint32 then = 0;
  float delta = 0;
  float accumulator = 0;
  float timeStep = IWandererCore::TIME_STEP;

  while (running) {
    then = now;
    now = SDL_GetTicks();
    auto ms = now - then;
    delta = static_cast<float>(ms / 1000.0f);

    HandleInput();

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
  }

  window->Hide();
}

void WandererControllerImpl::Quit() {
  running = false;
}

}