#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>
#include <cen/window.hpp>

#include "game.hpp"
#include "game_loop.hpp"

namespace wanderer {

class wanderer_app final
{
 public:
  wanderer_app();

  /**
   * \brief Runs the game.
   *
   * \return `0` on normal exit.
   */
  auto run() -> int;

 private:
  cen::window m_window;      ///< Application window.
  cen::renderer m_renderer;  ///< Renderer used for all rendering.
  game m_game;               ///< Provides game logic and game state.
  game_loop m_loop;          ///< Provides game loop logic and book-keeping.
  cen::mouse_state m_mouseState;  ///< Provides info about mouse state.
  cen::key_state m_keyState;      ///< Provides info about keyboard state.

  [[nodiscard]] auto handle_input() -> bool;
};

}  // namespace wanderer
