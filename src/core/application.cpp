#include "application.h"

#include <centurion.h>

#include "game.h"
#include "game_constants.h"
#include "game_loop.h"

using centurion::Renderer;
using centurion::Window;

namespace wanderer {
namespace {

Renderer create_renderer(const Window& window)
{
  Renderer renderer{window};
  renderer.set_logical_size({g_logicalWidth<>, g_logicalHeight<>});
  renderer.set_logical_integer_scale(true);
  return renderer;
}

}  // namespace

void run()
{
#ifdef NDEBUG
  Window window{"Wanderer", Screen::size()};
  window.set_fullscreen(true);
#else
  Window window{"Wanderer", {1440, 810}};
#endif

  Renderer renderer{create_renderer(window)};

  GameLoop loop;
  Game game{renderer};
  Input input;

  window.show();

  bool running{true};
  while (running) {
    input.update(renderer.output_width(), renderer.output_height());

    if (input.was_released(SDL_SCANCODE_ESCAPE) || input.was_quit_requested()) {
      running = false;
    }

    game.handle_input(input);

    loop.update(game);

    renderer.set_color(centurion::color::pink);
    renderer.clear();

    //    renderer.set_color(color::black);
    //    renderer.fill_rect({{0, 0}, {1000, 1000}});

    game.render(renderer, loop.alpha());
    renderer.present();
  }

  window.hide();
}

}  // namespace wanderer