#include "wanderer_engine.hpp"

#include "core/game_constants.hpp"

namespace wanderer {

wanderer_engine::wanderer_engine()
    : m_window{"Wanderer"}
    , m_graphics{m_window}
    , m_game{m_graphics}
{
  m_input.mouse.set_logical_size(glob::logical_size<>);

  // clang-format off
  m_game.sink<fullscreen_toggled_event>().connect<&wanderer_engine::on_fullscreen_toggled>(this);
  m_game.sink<integer_scaling_toggled_event>().connect<&wanderer_engine::on_integer_scaling_toggled>(this);
  // clang-format on
}

auto wanderer_engine::run() -> int
{
  m_window.show();

  fetch_current_time();
  m_game.on_start();

  auto& renderer = m_graphics.renderer();
  while (is_running())
  {
    tick();

    renderer.clear_with(cen::colors::black);
    m_game.render(m_graphics, m_input.mouse.position());
    renderer.present();
  }

  m_game.on_exit();
  m_window.hide();

  return 0;
}

auto wanderer_engine::update_input() -> bool
{
  m_input.mouse.update(m_graphics.renderer().output_size());
  m_input.keyboard.update();

  cen::event::update();

  m_game.handle_input(m_input);

  return !m_game.quit_requested() && !cen::event::in_queue(cen::event_type::quit);
}

void wanderer_engine::update_logic(const delta_time dt)
{
  m_game.tick(dt);
}

void wanderer_engine::on_fullscreen_toggled(const fullscreen_toggled_event& event)
{
  // TODO make it possible to specify whether to use real fullscreen or fullscreen desktop
  if (event.enabled)
  {
    m_window.set_size(cen::screen::size().value());
    m_window.set_fullscreen_desktop(true);
  }
  else
  {
    m_window.set_fullscreen_desktop(false);
    m_window.set_width(cen::screen::width().value() / 2);
    m_window.set_height(cen::screen::height().value() / 2);
  }
}

void wanderer_engine::on_integer_scaling_toggled(
    const integer_scaling_toggled_event& event)
{
  m_graphics.renderer().set_logical_integer_scale(event.enabled);
}

}  // namespace wanderer