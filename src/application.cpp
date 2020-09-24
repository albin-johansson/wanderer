#include "application.hpp"

#include <SDL.h>

#include <algorithm>  // min
#include <counter.hpp>
#include <key_code.hpp>
#include <screen.hpp>

#include "game_constants.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window};
  renderer.set_logical_size({g_logicalWidth<>, g_logicalHeight<>});
  renderer.set_logical_integer_scale(true);
  return renderer;
}

[[nodiscard]] auto was_quit_requested() noexcept -> bool
{
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}  // namespace

application::application()
    : m_window{"Wanderer", {1440, 810}},
      m_renderer{create_renderer(m_window)},
      m_game{m_renderer}
{}

auto application::handle_input() -> bool
{
  m_mouseState.update(m_renderer.output_width(), m_renderer.output_height());
  m_keyState.update();
  SDL_PumpEvents();

  const bool shouldContinue =
      !m_keyState.was_just_released(cen::keycodes::escape) &&
      !was_quit_requested();

  m_game.handle_input(m_mouseState, m_keyState);

  return shouldContinue;
}

void application::run()
{
  constexpr double tickRate{60};
  constexpr int maxSteps{5};
  constexpr cen::seconds<double> fixedDelta{1.0 / tickRate};

  m_window.show();

  auto currentTime = cen::counter::now_sec<double>();

  bool running = true;
  while (running) {
    const auto newTime = cen::counter::now_sec<double>();
    auto frameTime = newTime - currentTime;
    currentTime = newTime;

    auto nSteps = 0;
    while (frameTime > cen::seconds<double>::zero()) {
      if (nSteps > maxSteps) {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      const auto deltaTime = std::min(frameTime, fixedDelta);

      running = handle_input();
      if (!running) {
        break;
      }

      m_game.tick(delta{static_cast<float>(deltaTime.count())});

      frameTime -= deltaTime;

      ++nSteps;
    }

    m_renderer.clear_with(cen::colors::pink);
    m_game.render(m_renderer, alpha{0});
    m_renderer.present();
  }

  m_window.hide();
}

}  // namespace wanderer