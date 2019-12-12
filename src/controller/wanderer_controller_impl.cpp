#include "wanderer_controller_impl.h"
#include "window.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "image_generator.h"
#include "display_modes.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

WandererControllerImpl::WandererControllerImpl() {
  SDL_DisplayMode desktop = DisplayModes::GetDesktopInfo();

#ifdef NDEBUG
  window = Window::Create("Wanderer", desktop.w, desktop.h);
  window->SetFullscreen(true);
#else
  window = Window::Create("Wanderer", 1280, 720);
  window->SetFullscreen(false);
#endif

  InitIcon();

  renderer = Renderer::Create(window->GetInternalWindow());
  renderer->SetLogicalSize(LOGICAL_WIDTH, LOGICAL_HEIGHT);

  auto imageGenerator = std::make_unique<ImageGenerator>(renderer);
  core = CreateCore(*imageGenerator);
  core->SetViewportWidth(LOGICAL_WIDTH);
  core->SetViewportHeight(LOGICAL_HEIGHT);

  keyStateManager = std::make_shared<KeyStateManager>();
  mouseStateManager = std::make_shared<MouseStateManager>();

  mouseStateManager->SetLogicalWidth(LOGICAL_WIDTH);
  mouseStateManager->SetLogicalHeight(LOGICAL_HEIGHT);

  // TODO setters need to be called every time the window size changes
  mouseStateManager->SetWindowWidth(window->GetWidth());
  mouseStateManager->SetWindowHeight(window->GetHeight());

  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(keyStateManager,
                                                       mouseStateManager,
                                                       static_cast<float>(desktop.refresh_rate));
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::InitIcon() {
  SDL_Surface* icon = IMG_Load("resources/img/tactile_icon.png");
  if (icon != nullptr) {
    window->SetIcon(icon);
    SDL_FreeSurface(icon);
  } else {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_WARN,
                   "Failed to load window icon! %s", SDL_GetError());
  }
}

void WandererControllerImpl::Run() {
  window->Show();

  while (!core->ShouldQuit()) {
    gameLoop->Update(*core, *renderer);
  }

  window->Hide();
}

}