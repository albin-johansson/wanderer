#pragma once
#include "renderer.h"

namespace albinjohansson::wanderer {

class IWandererCore;

/**
 * The IGameLoop interface specifies objects that represent various kinds of game loops that serve
 * as the heart of the game.
 *
 * @since 0.1.0
 */
class IGameLoop {
 public:
  virtual ~IGameLoop() = default;

  /**
   * Updates the state of the loop.
   *
   * @param core a reference to the wanderer core that will be updated.
   * @param renderer a reference to the renderer that will be used.
   * @since 0.1.0
   */
  virtual void update(IWandererCore& core, centurion::Renderer& renderer) = 0;
};

}