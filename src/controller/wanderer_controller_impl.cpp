#include "wanderer_controller_impl.h"

#include <key_state.h>
#include <mouse_state.h>
#include <screen.h>
#include <texture_loader.h>

#include <memory>

#include "game_constants.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_builder.h"

using namespace centurion;
using namespace centurion::input;

namespace albinjohansson::wanderer {

WandererControllerImpl::WandererControllerImpl()
{
#ifdef NDEBUG
  m_window = Window::unique("Wanderer", Screen::width(), Screen::height());
  m_window->set_fullscreen(true);
#else
  m_window = Window::unique("Wanderer", 1280, 720);
#endif

  m_renderer = std::make_unique<Renderer>(*m_window);
  m_renderer->set_logical_size(GameConstants::logical_width,
                               GameConstants::logical_height);

  TextureLoader textureLoader{m_renderer};
  m_core = WandererCoreBuilder::build(textureLoader);
  m_core->set_viewport_width(GameConstants::logical_width);
  m_core->set_viewport_height(GameConstants::logical_height);

  auto mouseState = MouseState::shared();
  mouseState->set_logical_width(GameConstants::logical_width);
  mouseState->set_logical_height(GameConstants::logical_height);
  mouseState->set_window_width(m_window->width());
  mouseState->set_window_height(m_window->height());

  m_window->add_window_listener(mouseState);

  const auto refreshRate = static_cast<float>(Screen::refresh_rate());
  m_gameLoop = std::make_unique<SmoothFixedTimestepLoop>(
      std::make_unique<KeyState>(), mouseState, refreshRate);
}

WandererControllerImpl::~WandererControllerImpl() = default;

void WandererControllerImpl::run()
{
  m_window->show();

  while (!m_core->should_quit()) {
    m_gameLoop->update(*m_core, *m_renderer);
  }

  m_window->hide();
}

}  // namespace albinjohansson::wanderer