#pragma once
#include "wanderer_core.h"
#include "renderer.h"
#include <memory>

namespace wanderer::controller {

/**
 * The IGameLoop interface specifies objects that represent various kinds of game loops that serve
 * as the heart of the game.
 *
 * @since 0.1.0
 */
class IGameLoop {
 protected:
  IGameLoop() = default;

 public:
  virtual ~IGameLoop() = default;

  /**
   * Updates the state of the loop.
   *
   * @param core a reference to the wanderer core that will be updated.
   * @param renderer a reference to the renderer that will be used.
   * @since 0.1.0
   */
  virtual void Update(core::IWandererCore& core, visuals::Renderer& renderer) = 0;

//  /**
//   * Indicates whether or not the game should quit.
//   *
//   * @return true if the game should quit; false otherwise.
//   * @since 0.1.0
//   */
//  [[nodiscard]] virtual bool ShouldQuit() const noexcept = 0;
};

using IGameLoop_uptr = std::unique_ptr<IGameLoop>;
using IGameLoop_sptr = std::shared_ptr<IGameLoop>;
using IGameLoop_wptr = std::weak_ptr<IGameLoop>;

}