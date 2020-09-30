#include "application.hpp"

#include <SDL.h>

#include <algorithm>  // min
#include <cen/counter.hpp>
#include <cen/event.hpp>
#include <cen/screen.hpp>

#include "game_constants.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_renderer(const cen::window& window) -> cen::renderer
{
  cen::renderer renderer{window};

  const auto typewriter = "resource/font/type_writer.ttf";
  renderer.emplace_font("typewriter_s"_hs, typewriter, 8);
  renderer.emplace_font("typewriter_m"_hs, typewriter, 16);
  renderer.emplace_font("typewriter_l"_hs, typewriter, 24);

  renderer.set_logical_size({g_logicalWidth<>, g_logicalHeight<>});
  renderer.set_logical_integer_scale(true);

  return renderer;
}

[[nodiscard]] auto was_quit_requested() noexcept -> bool
{
  return cen::event::num_queued(cen::event_type::quit) > 0;
}

}  // namespace

application::application()
#ifndef NDEBUG
    : m_window{"Wanderer", {1440, 810}},
#else
    : m_window{"Wanderer", cen::screen::size()},
#endif
      m_renderer{create_renderer(m_window)},
      m_game{m_renderer}
{
#ifdef NDEBUG
  m_window.set_fullscreen(true);
#endif

  m_mouseState.set_logical_width(g_logicalWidth<int>);
  m_mouseState.set_logical_height(g_logicalHeight<int>);
}

auto application::handle_input() -> bool
{
  m_mouseState.update(m_renderer.output_width(), m_renderer.output_height());
  m_keyState.update();
  cen::event::refresh();

  m_game.handle_input(m_mouseState, m_keyState);

  const bool shouldContinue = !m_game.quit_requested() && !was_quit_requested();

  return shouldContinue;
}

void application::run()
{
  constexpr int maxSteps{5};
  const auto tickRate = static_cast<double>(cen::screen::refresh_rate());
  const cen::seconds<double> fixedDelta{1.0 / tickRate};

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

      m_game.tick(delta{deltaTime.count()});

      frameTime -= deltaTime;

      ++nSteps;
    }

    m_renderer.clear_with(cen::colors::pink);
    m_game.render(m_renderer);
    m_renderer.present();
  }

  m_window.hide();
}

}  // namespace wanderer