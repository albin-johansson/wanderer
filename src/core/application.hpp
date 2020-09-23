/**
 * @brief Provides the "entry-point" for the Wanderer game.
 * @file application.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <renderer.hpp>
#include <window.hpp>

#include "game.hpp"
#include "game_loop.hpp"
#include "input.hpp"

namespace wanderer {

class application
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
  Game m_game;
  GameLoop m_loop;
  Input m_input;
};

}  // namespace wanderer
