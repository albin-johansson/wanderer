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
 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  friend Unique<IWandererController> create_controller();

  ~WandererControllerImpl() override;

  void run() override;

 private:
  Shared<IWandererCore> m_core = nullptr;
  Unique<IGameLoop> m_gameLoop = nullptr;
  Shared<ctn::Renderer> m_renderer = nullptr;
  Unique<ctn::Window> m_window = nullptr;

  /**
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  WandererControllerImpl();
};

}  // namespace albinjohansson::wanderer
