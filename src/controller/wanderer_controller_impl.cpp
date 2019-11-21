#include "wanderer_controller_impl.h"
#include <SDL.h>
#include "input.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"
#include "image_generator.h"
#include "font.h"
#include "display_modes.h"

using namespace wanderer::core;
using namespace wanderer::visuals;
using namespace wanderer::service;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl() {
  SDL_DisplayMode desktop = DisplayModes::GetDesktopInfo();
  window = Window::Create("Wanderer", desktop.w, desktop.h);
  window->SetFullscreen(true);

  SDL_Surface* icon = IMG_Load("resources/img/tactile_icon.png");
  if (icon != nullptr) {
    window->SetIcon(icon);
  } else {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_WARN,
                   "Failed to load window icon! %s", SDL_GetError());
  }

  renderer = Renderer::Create(window->GetInternalWindow());
  renderer->SetFont(Font::Create("resources/font/type_writer.ttf", 24));
  renderer->SetLogicalSize(LOGICAL_WIDTH, LOGICAL_HEIGHT);

  auto imageGenerator = ImageGenerator::Create(renderer);
  core = CreateCore(*imageGenerator);
  core->SetViewportWidth(LOGICAL_WIDTH);
  core->SetViewportHeight(LOGICAL_HEIGHT);
  
  keyStateManager = KeyStateManager::Create();
  mouseStateManager = MouseStateManager::Create();

  mouseStateManager->SetLogicalWidth(LOGICAL_WIDTH);
  mouseStateManager->SetLogicalHeight(LOGICAL_HEIGHT);

  // TODO setters need to be called every time the window size changes
  mouseStateManager->SetWindowWidth(window->GetWidth());
  mouseStateManager->SetWindowHeight(window->GetHeight());

  gameLoop = SmoothFixedTimestepLoop::Create(keyStateManager,
                                             mouseStateManager,
                                             static_cast<float>(desktop.refresh_rate));
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::Run() {
  window->Show();

  while (!core->ShouldQuit()) {
    gameLoop->Update(*core, *renderer);
  }

  window->Hide();
}

}