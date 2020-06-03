#include "application.h"

#include <centurion.h>

#include "game.h"
#include "game_constants.h"
#include "game_loop.h"

using namespace centurion;

namespace wanderer {
namespace {

Renderer create_renderer(const Window& window)
{
  Renderer renderer{window};
  renderer.set_logical_size({g_logicalWidth, g_logicalHeight});
  renderer.set_logical_integer_scale(false);
  return renderer;
}

}  // namespace

void run()
{
#ifdef NDEBUG
  Window window{"Wanderer", Screen::size()};
  window.set_fullscreen(true);
#else
  Window window{"Wanderer", {g_logicalWidth, g_logicalHeight}};
#endif

  Renderer renderer{create_renderer(window)};

  GameLoop loop;
  Game game;
  Input input;

  game.init();

  window.show();

  bool running{true};
  while (running) {
    input.update(renderer.output_width(), renderer.output_height());

    if (input.was_released(SDL_SCANCODE_ESCAPE) || input.was_quit_requested()) {
      running = false;
    }

    game.handle_input(input);

    loop.update(game);

    renderer.set_color(color::black);
    renderer.clear();
    game.render(renderer, loop.alpha());
    renderer.present();
  }

  window.hide();
}

}  // namespace wanderer