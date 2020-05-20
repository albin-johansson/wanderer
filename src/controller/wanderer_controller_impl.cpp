#include "wanderer_controller_impl.h"

#include <centurion.h>

#include <memory>

#include "game_constants.h"
#include "resource.h"
#include "smooth_fixed_timestep_loop.h"
#include "wanderer_core_builder.h"

using namespace centurion;
using namespace centurion::input;

namespace wanderer {
namespace {

void add_fonts(Renderer& renderer)
{
  const auto path = Resource::font("type_writer.ttf");
  auto sm = Font::shared(path.c_str(), 12);
  auto md = Font::shared(path.c_str(), 24);
  auto lg = Font::shared(path.c_str(), 38);
  renderer.add_font("tp-sm", sm);
  renderer.add_font("tp-md", md);
  renderer.add_font("tp-lg", lg);
}

}  // namespace

WandererControllerImpl::WandererControllerImpl()
{
#ifdef NDEBUG
  m_window = Window::unique("Wanderer", Screen::size());
  m_window->set_fullscreen(true);
#else
  m_window = Window::unique("Wanderer", {1280, 720});
#endif

  m_renderer = Renderer::unique(*m_window);
  m_renderer->set_logical_size(
      {GameConstants::logical_width, GameConstants::logical_height});
  m_renderer->set_logical_integer_scale(false);

  add_fonts(*m_renderer);

  TextureLoader textureLoader{m_renderer};
  m_core = WandererCoreBuilder::build(textureLoader);
  m_core->set_viewport_width(GameConstants::logical_width);
  m_core->set_viewport_height(GameConstants::logical_height);

  auto mouseState = MouseState::shared();
  mouseState->set_logical_width(GameConstants::logical_width);
  mouseState->set_logical_height(GameConstants::logical_height);

  const auto refreshRate = static_cast<float>(Screen::refresh_rate());
  m_gameLoop = std::make_unique<SmoothFixedTimestepLoop>(
      KeyState::unique(), mouseState, refreshRate);
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

}  // namespace wanderer