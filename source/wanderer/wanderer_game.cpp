#include "wanderer_game.hpp"

#include "data/cfg.hpp"

namespace wanderer {
namespace {

constexpr auto _window_flags = cen::window::hidden | cen::window::allow_high_dpi;

constexpr auto _renderer_flags = cen::renderer::accelerated |      //
                                 cen::renderer::target_textures |  //
                                 cen::renderer::vsync;

}  // namespace

wanderer_game::wanderer_game()
    : _cfg{make_game_cfg()}
    , _window{"Wanderer", cen::window::default_size(), _window_flags}
    , _renderer{_window.create_renderer(_renderer_flags)}
{
  _renderer.set_logical_size({_cfg.logical_size.x, _cfg.logical_size.y});
}

void wanderer_game::run()
{
  _window.set_fullscreen_desktop(true);
  _window.show();

  start();

  _window.hide();
}

void wanderer_game::process_events()
{
  cen::event_handler event;

  while (event.poll()) {
    if (event.is(cen::event_type::quit)) {
      stop();
      break;
    }
    else if (event.is(cen::event_type::key_up)) {
      const auto& ke = event.get<cen::keyboard_event>();
      if (ke.is_active(cen::scancodes::q)) {
        stop();
        break;
      }
    }
  }

  _keyboard.refresh();
}

void wanderer_game::update(const float32 dt)
{
  _dispatcher.update();

  // TODO
}

void wanderer_game::render()
{
  _renderer.clear_with(cen::colors::hot_pink);

  _renderer.present();
}

}  // namespace wanderer