#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
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

  window = std::make_unique<Window>("Wanderer", desktop.w, desktop.h);
  window->SetFullscreen(true);

  SDL_Surface* icon = IMG_Load("resources/tactile_icon.png");
  if (icon != nullptr) {
    window->SetIcon(icon);
  } else {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_WARN,
                   "Failed to load window icon! %s", SDL_GetError());
  }
  renderer = std::make_shared<Renderer>(window->GetInternalWindow());

  auto windowWidth = static_cast<float>(window->GetWidth());
  auto windowHeight = static_cast<float>(window->GetHeight());

  renderer->SetLogicalSize(LOGICAL_WIDTH, LOGICAL_HEIGHT);
  renderer->SetLogicalIntegerScale(true);
  renderer->SetViewport(Rectangle(0, 0, windowWidth, windowHeight));
  renderer->SetScale(windowWidth / LOGICAL_WIDTH, windowHeight / LOGICAL_HEIGHT);

  SDL_Log("Logical width: %i", renderer->GetLogicalWidth());
  SDL_Log("Logical height: %i", renderer->GetLogicalHeight());

  auto imgGen = std::make_shared<ImageGenerator>(renderer);
  core = CreateCore(imgGen);
  core->SetViewportWidth(LOGICAL_WIDTH);
  core->SetViewportHeight(LOGICAL_HEIGHT);

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