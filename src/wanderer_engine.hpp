#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>
#include <cen/window.hpp>

#include "game.hpp"
#include "graphics_context.hpp"
#include "semi_fixed_game_loop.hpp"

namespace wanderer {

/**
 * \class wanderer_app
 *
 * \brief Represents the Wanderer application.
 *
 * \details This is the top-level representation of the entire game that
 * handles the application window, input, game state/logic, etc.
 *
 * \since 0.1.0
 *
 * \headerfile wanderer_app.hpp
 */
class wanderer_engine final : public semi_fixed_game_loop
{
 public:
  /**
   * \brief Initializes the application.
   *
   * \details The application window will always be in windowed mode in debug
   * mode, in order to be able to debug the program with breakpoints.
   *
   * \since 0.1.0
   */
  wanderer_engine();

  /**
   * \brief Runs the game.
   *
   * \return `0` on normal exit.
   */
  auto run() -> int;

 protected:
  auto update_input() -> bool override;

  void update_logic(delta_t dt) override;

 private:
  cen::window m_window;           ///< Application window.
  graphics_context m_graphics;    ///< Graphics context used for all rendering.
  game m_game;                    ///< Provides game logic and game state.
  cen::mouse_state m_mouseState;  ///< Provides info about mouse state.
  cen::key_state m_keyState;      ///< Provides info about keyboard state.
};

}  // namespace wanderer
