#include "wanderer_controller_impl.h"
#include "window.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"
#include "image_generator.h"
#include "display_modes.h"
#include "game_constants.h"
#include <SDL.h>

using namespace centurion;

namespace albinjohansson::wanderer {

WandererControllerImpl::WandererControllerImpl() {
  SDL_DisplayMode desktop = DisplayModes::GetDesktopInfo();

#ifdef NDEBUG
  window = std::make_unique<Window>("Wanderer", desktop.w, desktop.h);
  window->set_fullscreen(true);
#else
  window = std::make_unique<Window>("Wanderer", 1280, 720);
  window->set_fullscreen(false);
#endif

  InitIcon();

  renderer = std::make_unique<Renderer>(*window);
  renderer->set_logical_size(gameLogicalWidth, gameLogicalHeight);

  ImageGenerator imageGenerator{renderer};
  core = create_core(imageGenerator);
  core->set_viewport_width(gameLogicalWidth);
  core->set_viewport_height(gameLogicalHeight);

  auto mouseStateManager = std::make_unique<MouseStateManager>();
  mouseStateManager->set_logical_width(gameLogicalWidth);
  mouseStateManager->set_logical_height(gameLogicalHeight);

  window->add_window_listener(mouseStateManager.get());

  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(std::make_unique<KeyStateManager>(),
                                                       std::move(mouseStateManager),
                                                       static_cast<float>(desktop.refresh_rate));
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::InitIcon() {
  SDL_Surface* icon = IMG_Load("resources/img/tactile_icon.png");
  if (icon) {
    window->set_icon(icon);
    SDL_FreeSurface(icon);
  } else {
    SDL_Log("Failed to load window icon! %s", SDL_GetError());
  }
}

void WandererControllerImpl::run() {
  window->show();

  while (!core->should_quit()) {
    gameLoop->update(*core, *renderer);
  }

  window->hide();
}

}