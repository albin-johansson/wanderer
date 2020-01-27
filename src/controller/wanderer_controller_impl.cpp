#include "wanderer_controller_impl.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state.h"
#include "mouse_state.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"
#include "image_generator.h"
#include "game_constants.h"
#include <system.h>
#include <SDL.h>

using namespace centurion;

namespace albinjohansson::wanderer {

WandererControllerImpl::WandererControllerImpl() {
#ifdef NDEBUG
  window = std::make_unique<Window>("Wanderer", Screen::get_width(), Screen::get_height());
  window->set_fullscreen(true);
#else
  window = std::make_unique<Window>("Wanderer", 1280, 720);
#endif

  renderer = std::make_unique<Renderer>(*window);
  renderer->set_logical_size(GameConstants::logical_width, GameConstants::logical_height);

  ImageGenerator imageGenerator{renderer};
  core = create_core(imageGenerator);
  core->set_viewport_width(GameConstants::logical_width);
  core->set_viewport_height(GameConstants::logical_height);

  auto mouseState = MouseState::unique();
  mouseState->set_logical_width(GameConstants::logical_width);
  mouseState->set_logical_height(GameConstants::logical_height);
  mouseState->set_window_width(window->get_width());
  mouseState->set_window_height(window->get_height());

  window->add_window_listener(mouseState.get());

  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(std::make_unique<KeyState>(),
                                                       std::move(mouseState),
                                                       static_cast<float>(Screen::get_refresh_rate()));
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::run() {
  window->show();

  while (!core->should_quit()) {
    gameLoop->update(*core, *renderer);
  }

  window->hide();
}

}