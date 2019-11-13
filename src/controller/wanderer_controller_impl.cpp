#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "bad_state_exception.h"
#include "objects.h"
#include "input.h"
#include "smooth_fixed_timestep_loop.h"

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core) {
  this->core = Objects::RequireNonNull(std::move(core));

  SDL_DisplayMode desktop = GetDesktopInfo();

  window = std::make_unique<Window>("Wanderer", desktop.w, desktop.h);
  window->SetFullscreen(true);

  SDL_Surface* icon = IMG_Load("resources/tactile_icon.png");
  if (icon != nullptr) {
    window->SetIcon(icon);
  } else {
    SDL_Log("Failed to load window icon: %s", SDL_GetError());
  }

  this->core->SetViewportWidth(static_cast<float>(window->GetWidth()));
  this->core->SetViewportHeight(static_cast<float>(window->GetHeight()));

  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
  keyStateManager = std::make_shared<KeyStateManager>();

  auto vsyncDelta = static_cast<float>(desktop.refresh_rate);
  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(keyStateManager, vsyncDelta);
}

WandererControllerImpl::~WandererControllerImpl() = default;

SDL_DisplayMode WandererControllerImpl::GetDesktopInfo() {
  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
    throw BadStateException();
  }
  return dm;
}

void WandererControllerImpl::Run() {
  running = true;
  window->Show();

  while (running && !gameLoop->ShouldQuit()) {
    gameLoop->Update(*core, *renderer);
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