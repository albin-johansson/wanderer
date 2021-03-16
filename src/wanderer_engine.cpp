#include "wanderer_engine.hpp"

#include "game_constants.hpp"

namespace wanderer {

wanderer_engine::wanderer_engine()
    : m_window{"Wanderer"}
    , m_graphics{m_window}
    , m_game{m_graphics}
{
  if constexpr (cen::is_debug_build()) {
    m_window.set_width(cen::screen::width() / 2);
    m_window.set_height(cen::screen::height() / 2);
  } else {
    m_window.set_size(cen::screen::size());
    m_window.set_fullscreen(true);
  }

  m_mouseState.set_logical_width(glob::logical_width<>);
  m_mouseState.set_logical_height(glob::logical_height<>);
}

auto wanderer_engine::run() -> int
{
  auto& renderer = m_graphics.renderer();

  m_window.show();
  fetch_current_time();

  while (is_running()) {
    tick();

    renderer.clear_with(cen::colors::black);
    m_game.render(m_graphics, m_mouseState.mouse_pos());
    renderer.present();
  }

  m_window.hide();

  return 0;
}

auto wanderer_engine::update_input() -> bool
{
  const auto& renderer = m_graphics.renderer();
  m_mouseState.update(renderer.output_width(), renderer.output_height());
  m_keyState.update();
  cen::event::refresh();

  m_game.handle_input(m_mouseState, m_keyState);

  const bool shouldContinue =
      !m_game.quit_requested() &&
      cen::event::queue_count(cen::event_type::quit) == 0;

  return shouldContinue;
}

void wanderer_engine::update_logic(const delta_t dt)
{
  m_game.tick(dt);
}

}  // namespace wanderer