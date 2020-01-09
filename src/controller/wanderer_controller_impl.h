#pragma once
#include <memory>
#include "wanderer_controller.h"
#include "window.h"
#include "wanderer_core.h"
#include "game_loop.h"

namespace centurion {

class Renderer;

}

namespace albinjohansson::wanderer {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  std::unique_ptr<IWandererCore> core = nullptr;
  std::unique_ptr<IGameLoop> gameLoop = nullptr;
  std::shared_ptr<centurion::Renderer> renderer = nullptr;
  std::unique_ptr<centurion::Window> window = nullptr;

  /**
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  WandererControllerImpl();

  void init_icon();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  friend std::unique_ptr<IWandererController> create_controller();

  ~WandererControllerImpl() override;

  void run() override;
};

}
