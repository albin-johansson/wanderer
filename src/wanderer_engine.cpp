#include "wanderer_engine.hpp"

#include "game_constants.hpp"

namespace wanderer {

wanderer_engine::wanderer_engine()
    : m_window{"Wanderer"}
    , m_graphics{m_window}
    , m_game{m_graphics}
{
  if constexpr (cen::is_debug_build())
  {
    // m_window.set_width(cen::screen::width() / 2);
    // m_window.set_height(cen::screen::height() / 2);
    m_window.set_size(cen::screen::size());
    m_window.set_fullscreen_desktop(true);
  }
  else
  {
    m_window.set_size(cen::screen::size());
    m_window.set_fullscreen(true);
  }

  m_input.mouse.set_logical_size(glob::logical_size<>);
}

auto wanderer_engine::run() -> int
{
  auto& renderer = m_graphics.renderer();

  m_window.show();
  fetch_current_time();

  while (is_running())
  {
    tick();

    renderer.clear_with(cen::colors::black);
    m_game.render(m_graphics, m_input.mouse.position());
    renderer.present();
  }

  m_window.hide();

  return 0;
}

auto wanderer_engine::update_input() -> bool
{
  const auto& renderer = m_graphics.renderer();
  m_input.mouse.update(renderer.output_size());
  m_input.keyboard.update();
  cen::event::refresh();

  m_game.handle_input(m_input);

  return !m_game.quit_requested() &&
         !cen::event::in_queue(cen::event_type::quit);
}

void wanderer_engine::update_logic(const delta_t dt)
{
  m_game.tick(dt);
}

}  // namespace wanderer