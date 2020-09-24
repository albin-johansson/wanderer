#include "application.hpp"

#include <screen.hpp>

#include "game_constants.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window};
  renderer.set_logical_size({g_logicalWidth<>, g_logicalHeight<>});
  renderer.set_logical_integer_scale(true);
  return renderer;
}

}  // namespace

application::application()
    : m_window{"Wanderer", {1440, 810}},
      m_renderer{create_renderer(m_window)},
      m_game{m_renderer}
{}

void application::run()
{
  m_window.show();

  bool running{true};
  while (running) {
    m_input.update(m_renderer.output_width(), m_renderer.output_height());

    if (m_input.was_released(SDLK_ESCAPE) || m_input.was_quit_requested()) {
      running = false;
    }

    m_game.handle_input(m_input);

    m_loop.update(m_game);

    m_renderer.clear_with(cen::colors::pink);
    m_game.render(m_renderer, m_loop.curr_alpha());
    m_renderer.present();
  }

  m_window.hide();
}

}  // namespace wanderer