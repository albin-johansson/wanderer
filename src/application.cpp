#include "application.hpp"

#include <cen/event.hpp>

#include "game_constants.hpp"
#include "make_renderer.hpp"

namespace wanderer {

application::application()
#ifndef NDEBUG
    : m_window{"Wanderer", {1440, 810}}
    ,
#else
    : m_window{"Wanderer", cen::screen::size()}
    ,
#endif
    m_renderer{make_renderer(m_window)}
    , m_game{m_renderer}
{
#ifdef NDEBUG
  m_window.set_fullscreen(true);
#endif

  m_mouseState.set_logical_width(g_logicalWidth<int>);
  m_mouseState.set_logical_height(g_logicalHeight<int>);
}

auto application::handle_input() -> bool
{
  m_mouseState.update(m_renderer.output_width(), m_renderer.output_height());
  m_keyState.update();
  cen::event::refresh();

  m_game.handle_input(m_mouseState, m_keyState);

  const bool shouldContinue =
      !m_game.quit_requested() &&
      cen::event::num_queued(cen::event_type::quit) == 0;

  return shouldContinue;
}

void application::run()
{
  const auto input = [&] {
    return handle_input();
  };

  const auto logic = [&](const delta dt) {
    m_game.tick(dt);
  };

  m_window.show();
  m_loop.fetch_current_time();
  while (m_loop.running()) {
    m_loop.tick(input, logic);

    m_renderer.clear_with(cen::colors::pink);
    m_game.render(m_renderer);
    m_renderer.present();
  }

  m_window.hide();
}

}  // namespace wanderer