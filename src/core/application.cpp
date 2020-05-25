#include "application.h"

#include <centurion.h>

#include "game.h"
#include "game_loop.h"

using namespace centurion;

namespace wanderer {
namespace {

inline constexpr int maxFrameTime = 15;

void smooth_delta(GameLoop& loop) noexcept
{
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  loop.delta += loop.deltaBuffer;

  int frameCount = static_cast<int>(loop.delta * loop.vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  const float oldDelta = loop.delta;
  loop.delta = static_cast<float>(frameCount) / loop.vsyncRate;
  loop.deltaBuffer = oldDelta - loop.delta;
}

void update(GameLoop& loop, Game& game)
{
  loop.then = loop.now;
  loop.now = Timer::high_res();

  loop.delta = static_cast<float>(loop.now - loop.then) / loop.counterFreq;

  if (loop.delta > maxFrameTime) {
    loop.delta = maxFrameTime;
  }

  smooth_delta(loop);

  loop.accumulator += loop.delta;

  while (loop.accumulator >= loop.timeStep) {
    loop.accumulator -= loop.timeStep;
    game.tick(loop.timeStep);
  }
}

}  // namespace

void Application::run()
{
  Window window;
  Renderer renderer{window};

  GameLoop loop;  // actually just game loop data
  loop.vsyncRate = static_cast<float>(Screen::refresh_rate());
  loop.timeStep = 1.0f / loop.vsyncRate;
  loop.counterFreq = static_cast<float>(Timer::high_res_freq());
  loop.now = Timer::high_res();
  loop.then = loop.now;

  Game game;
  Input input;

  window.show();

  bool running = true;
  while (running) {
    input.update(renderer.output_width(), renderer.output_height());

    if (input.was_released(SDL_SCANCODE_ESCAPE) || input.was_quit_requested()) {
      running = false;
    }

    game.handle_input(input);

    update(loop, game);

    float alpha = loop.accumulator / loop.timeStep;
    if (alpha > 1.0f) {
      alpha = 1.0f;
    }

    renderer.set_color(color::black);
    renderer.clear();

    game.render(renderer, alpha);

    renderer.present();
  }

  window.hide();
}

}  // namespace wanderer