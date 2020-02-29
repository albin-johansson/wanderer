#include "wanderer_controller_impl.h"

#include <key_state.h>
#include <mouse_state.h>
#include <screen.h>
#include <texture_loader.h>

#include <memory>

#include "game_constants.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_factory.h"

using namespace centurion;
using namespace centurion::video;
using namespace centurion::system;
using namespace centurion::input;

namespace albinjohansson::wanderer {

WandererControllerImpl::WandererControllerImpl()
{
#ifdef NDEBUG
  window = std::make_unique<Window>(
      "Wanderer", Screen::get_width(), Screen::get_height());
  window->set_fullscreen(true);
#else
  window = std::make_unique<Window>("Wanderer", 1280, 720);
#endif

  renderer = std::make_unique<Renderer>(*window);
  renderer->set_logical_size(GameConstants::logical_width,
                             GameConstants::logical_height);

  ImageGenerator imageGenerator{renderer};
  core = create_core(imageGenerator);
  core->set_viewport_width(GameConstants::logical_width);
  core->set_viewport_height(GameConstants::logical_height);

  auto mouseState = MouseState::shared();
  mouseState->set_logical_width(GameConstants::logical_width);
  mouseState->set_logical_height(GameConstants::logical_height);
  mouseState->set_window_width(window->get_width());
  mouseState->set_window_height(window->get_height());

  window->add_window_listener(mouseState);

  const auto refreshRate = static_cast<float>(Screen::get_refresh_rate());
  gameLoop = std::make_unique<SmoothFixedTimestepLoop>(
      std::make_unique<KeyState>(), mouseState, refreshRate);
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::run()
{
  window->show();

  while (!core->should_quit()) {
    gameLoop->update(*core, *renderer);
  }

  window->hide();
}

}  // namespace albinjohansson::wanderer