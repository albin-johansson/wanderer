#include "wanderer_controller_impl.h"
#include <SDL.h>
#include "bad_state_exception.h"
#include "input.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"
#include "image_generator.h"

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl() {
  SDL_DisplayMode desktop = GetDesktopInfo();
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                 SDL_LOG_PRIORITY_INFO,
                 "Desktop refresh rate: %i Hz", desktop.refresh_rate);

  window = Window::CreateUnique("Wanderer", desktop.w, desktop.h);
  window->SetFullscreen(true);

  SDL_Surface* icon = IMG_Load("resources/tactile_icon.png");
  if (icon != nullptr) {
    window->SetIcon(icon);
  } else {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_WARN,
                   "Failed to load window icon! %s", SDL_GetError());
  }

  renderer = Renderer::CreateUnique(window->GetInternalWindow());
  renderer->SetLogicalSize(LOGICAL_WIDTH, LOGICAL_HEIGHT);

  SDL_Log("Logical width: %i", renderer->GetLogicalWidth());
  SDL_Log("Logical height: %i", renderer->GetLogicalHeight());

  ImageGenerator_sptr imageGen = ImageGenerator::CreateUnique(renderer);
  core = CreateCore(imageGen);
  core->SetViewportWidth(LOGICAL_WIDTH);
  core->SetViewportHeight(LOGICAL_HEIGHT);

  keyStateManager = KeyStateManager::CreateUnique();

  mouseStateManager = MouseStateManager::CreateUnique();
  mouseStateManager->SetLogicalWidth(LOGICAL_WIDTH);
  mouseStateManager->SetLogicalHeight(LOGICAL_HEIGHT);

  // TODO setters need to be called every time the window size changes
  mouseStateManager->SetWindowWidth(window->GetWidth());
  mouseStateManager->SetWindowHeight(window->GetHeight());

  auto vsyncDelta = static_cast<float>(desktop.refresh_rate);
  gameLoop = SmoothFixedTimestepLoop::CreateUnique(keyStateManager,
                                                   mouseStateManager,
                                                   vsyncDelta);
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