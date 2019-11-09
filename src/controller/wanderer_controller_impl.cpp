#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <SDL_image.h>
#include "objects.h"
#include <iostream>

using namespace wanderer::core;
using namespace wanderer::view;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core) {
  this->core = Objects::RequireNonNull(std::move(core));
  window = std::make_unique<Window>("Wanderer", 1000, 800);
  window->SetFullscreen(false);
  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::HandleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type==SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE) {
      Quit();
    }
  }
}

void WandererControllerImpl::SavePositions() {
  core->SavePositions();
}

void WandererControllerImpl::Update(float delta) {
  core->Update();
}

void WandererControllerImpl::Render(float delta) {
  core->Render(*renderer);
}

void WandererControllerImpl::Interpolate(float alpha) {
  core->Interpolate(alpha);
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
    delta = static_cast<float>(ms/1000.0f);

    HandleInput();

    if (delta > MAX_FRAME_TIME) {
      delta = MAX_FRAME_TIME;
    }

    accumulator += delta;

    while (accumulator >= timeStep) {
      SavePositions();
      Update(timeStep);
      accumulator -= timeStep;
      Interpolate(accumulator/timeStep);
    }

    Render(delta);

    renderer->Present();
  }

  window->Hide();
}

void WandererControllerImpl::Quit() {
  running = false;
}

}