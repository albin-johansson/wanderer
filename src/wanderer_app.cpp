#include "wanderer_app.hpp"

#include <cen/event.hpp>

#include "game_constants.hpp"

namespace wanderer {

wanderer_app::wanderer_app()
#ifndef NDEBUG
    : m_window{"Wanderer", {1440, 810}}
    ,
#else
    : m_window{"Wanderer", cen::screen::size()}
    ,
#endif
    m_graphics{m_window}
    , m_game{m_graphics}
{
#ifdef NDEBUG
  m_window.set_fullscreen(true);
#endif

  m_mouseState.set_logical_width(g_logicalWidth<int>);
  m_mouseState.set_logical_height(g_logicalHeight<int>);
}

auto wanderer_app::handle_input() -> bool
{
  const auto& renderer = m_graphics.renderer();
  m_mouseState.update(renderer.output_width(), renderer.output_height());
  m_keyState.update();
  cen::event::refresh();

  m_game.handle_input(m_mouseState, m_keyState);

  const bool shouldContinue =
      !m_game.quit_requested() &&
      cen::event::num_queued(cen::event_type::quit) == 0;

  return shouldContinue;
}

auto wanderer_app::run() -> int
{
  const auto input = [this] {
    return handle_input();
  };

  const auto logic = [this](const delta_t dt) {
    m_game.tick(dt);
  };

  auto& renderer = m_graphics.renderer();

  m_window.show();
  m_loop.fetch_current_time();

  while (m_loop.running()) {
    m_loop.tick(input, logic);

    renderer.clear_with(cen::colors::black);
    m_game.render(renderer);
    renderer.present();
  }

  m_window.hide();

  return 0;
}

}  // namespace wanderer