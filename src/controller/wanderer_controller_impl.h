#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "game_loop.h"
#include "window.h"
#include <memory>

namespace albinjohansson::wanderer {

class Renderer;
class KeyStateManager;
class MouseStateManager;

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  // 1280x720, 1366x768, 1600x900
  static constexpr float LOGICAL_WIDTH = 1280;
  static constexpr float LOGICAL_HEIGHT = 720;

  std::unique_ptr<Window> window = nullptr;
  std::unique_ptr<IWandererCore> core = nullptr;
  std::unique_ptr<IGameLoop> gameLoop = nullptr;
  std::shared_ptr<Renderer> renderer = nullptr;
  std::shared_ptr<KeyStateManager> keyStateManager = nullptr;
  std::shared_ptr<MouseStateManager> mouseStateManager = nullptr;

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
