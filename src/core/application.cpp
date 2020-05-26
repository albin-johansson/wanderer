#include "application.h"

#include <centurion.h>

#include "game.h"
#include "game_loop.h"

using namespace centurion;

namespace wanderer {
namespace {



}  // namespace

void Application::run()
{
  Window window;
  Renderer renderer{window};

  GameLoop loop;
  Game game;
  Input input;

  game.init();

  window.show();

  bool running = true;
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