#pragma once
#include "wanderer_controller.h"
#include "window.h"
#include "wanderer_core.h"
#include "game_loop.h"
#include <memory>

namespace albinjohansson::wanderer {

class Renderer;

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  std::unique_ptr<Window> window = nullptr;
  std::unique_ptr<IWandererCore> core = nullptr;
  std::unique_ptr<IGameLoop> gameLoop = nullptr;
  std::shared_ptr<Renderer> renderer = nullptr;

  /**
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  WandererControllerImpl();

  void InitIcon();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  friend std::unique_ptr<IWandererController> CreateController();

  ~WandererControllerImpl() override;

  void Run() override;
};

}
