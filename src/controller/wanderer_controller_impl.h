#pragma once
#include "wanderer_controller.h"
#include <memory>
#include <window.h>
#include <renderer.h>
#include "wanderer_stdinc.h"
#include "wanderer_core.h"
#include "game_loop.h"

namespace albinjohansson::wanderer {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  unique<IWandererCore> core = nullptr;
  unique<IGameLoop> gameLoop = nullptr;
  shared<centurion::Renderer> renderer = nullptr;
  unique<centurion::Window> window = nullptr;

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

}
