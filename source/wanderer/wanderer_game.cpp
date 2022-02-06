#include "wanderer_game.hpp"

#include "wanderer/data/constants.hpp"

namespace wanderer {
namespace {

constexpr auto _window_flags = cen::window::hidden | cen::window::allow_high_dpi;

constexpr auto _renderer_flags = cen::renderer::accelerated |      //
                                 cen::renderer::target_textures |  //
                                 cen::renderer::vsync;

}  // namespace

wanderer_game::wanderer_game()
    : _window{"Wanderer", cen::window::default_size(), _window_flags}
    , _renderer{_window.create_renderer(_renderer_flags)}
{
  _renderer.set_logical_size({logical_width, logical_height});
  _mouse.set_logical_size({logical_width_f, logical_height_f});
}

void wanderer_game::run()
{
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