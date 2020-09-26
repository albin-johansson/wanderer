#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>
#include <cen/window.hpp>

#include "game.hpp"

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
  cen::mouse_state m_mouseState;
  cen::key_state m_keyState;

  [[nodiscard]] auto handle_input() -> bool;
};

}  // namespace wanderer
