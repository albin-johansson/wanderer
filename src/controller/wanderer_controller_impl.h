#pragma once
#include <renderer.h>
#include <window.h>

#include <memory>

#include "game_loop.h"
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The WandererControllerImpl class is an implementation of the
 * IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  unique<IWandererCore> core = nullptr;
  unique<IGameLoop> gameLoop = nullptr;
  shared<centurion::video::Renderer> renderer = nullptr;
  unique<centurion::video::Window> window = nullptr;

  /**
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  WandererControllerImpl();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  friend unique<IWandererController> create_controller();

  ~WandererControllerImpl() override;

  void run() override;
};

}  // namespace albinjohansson::wanderer
