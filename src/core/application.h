/**
 * @brief Provides the "entry-point" for the Wanderer game.
 * @file application.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <renderer.hpp>
#include <window.hpp>

#include "game.h"
#include "game_loop.h"
#include "input.h"

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
