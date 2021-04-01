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

  // clang-format off
  m_game.sink<comp::fullscreen_toggled_event>()
        .connect<&wanderer_engine::on_fullscreen_toggled>(this);
  m_game.sink<comp::integer_scaling_toggled_event>()
        .connect<&wanderer_engine::on_integer_scaling_toggled>(this);
  // clang-format on
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

void wanderer_engine::on_fullscreen_toggled(
    const comp::fullscreen_toggled_event& event)
{
  if (event.enabled)
  {
    m_window.set_size(cen::screen::size());
    m_window.set_fullscreen(true);
  }
  else
  {
    m_window.set_fullscreen(false);
    m_window.set_width(cen::screen::width() / 2);
    m_window.set_height(cen::screen::height() / 2);
  }
}

void wanderer_engine::on_integer_scaling_toggled(
    const comp::integer_scaling_toggled_event& event)
{
  m_graphics.renderer().set_logical_integer_scale(event.enabled);
}

}  // namespace wanderer