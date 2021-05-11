#pragma once

#include <centurion.hpp>  // window
#include <rune.hpp>       // input

#include "core/game.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/fullscreen_toggled_event.hpp"
#include "events/integer_scaling_toggled_event.hpp"
#include "semi_fixed_game_loop.hpp"

namespace wanderer {

/**
 * \class wanderer_engine
 *
 * \brief Represents the Wanderer engine.
 *
 * \details This is the top-level representation of the entire game that handles the
 * game window, graphics context, input, game state, etc.
 *
 * \since 0.1.0
 *
 * \headerfile wanderer_engine.hpp
 */
class wanderer_engine final : public semi_fixed_game_loop<wanderer_engine>
{
 public:
  /**
   * \brief Initializes the game.
   *
   * \since 0.1.0
   */
  wanderer_engine();

  /**
   * \brief Starts running the game.
   *
   * \return `0` on normal exit.
   */
  auto run() -> int;

  /**
   * \brief Updates the input state and checks if the game should quit.
   *
   * \return `true` if the game should continue running; `false` otherwise.
   */
  auto update_input() -> bool;

  /**
   * \brief Updates the game logic.
   *
   * \param dt the current delta time.
   */
  void update_logic(delta_time dt);

 private:
  cen::window m_window;         ///< Application window.
  graphics_context m_graphics;  ///< Graphics context used for all rendering.
  game m_game;                  ///< Provides game logic and game state.
  rune::input m_input;

  void on_fullscreen_toggled(const fullscreen_toggled_event& event);

  void on_integer_scaling_toggled(const integer_scaling_toggled_event& event);
};

}  // namespace wanderer
