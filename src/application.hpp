#pragma once

#include <renderer.hpp>
#include <window.hpp>

#include "game.hpp"
#include "game_loop.hpp"
#include "input.hpp"

namespace wanderer {

class application final
{
 public:
  application();

  /**
   * @brief Runs the game.
   */
  void run();

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  game m_game;
  game_loop m_loop;
  Input m_input;
};

}  // namespace wanderer
