#include "wanderer_controller_impl.h"
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
#endif

  init_icon();

  renderer = std::make_unique<Renderer>(*window);
  renderer->set_logical_size(GameConstants::logical_width, GameConstants::logical_height);

  ImageGenerator imageGenerator{renderer};
  core = create_core(imageGenerator);
  core->set_viewport_width(GameConstants::logical_width);
  core->set_viewport_height(GameConstants::logical_height);

  auto mouseStateManager = std::make_unique<MouseStateManager>();
  mouseStateManager->set_logical_width(GameConstants::logical_width);
  mouseStateManager->set_logical_height(GameConstants::logical_height);

  window->add_window_listener(mouseStateManager.get());

  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(std::make_unique<KeyStateManager>(),
                                                       std::move(mouseStateManager),
                                                       static_cast<float>(desktop.refresh_rate));
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::init_icon() {
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