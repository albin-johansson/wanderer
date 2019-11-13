#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "window.h"
#include "key_state_manager.h"
#include "game_loop.h"

namespace wanderer::controller {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  bool running = false;
  core::IWandererCore_uptr core = nullptr;
  visuals::Window_uptr window = nullptr;
  visuals::Renderer_uptr renderer = nullptr;
  KeyStateManager_sptr keyStateManager = nullptr;
  IGameLoop_uptr gameLoop = nullptr;

  /**
   * @param core a unique pointer to the associated core instance.
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @throws NullPointerException if the supplied pointer is nullptr.
   * @since 0.1.0
   */
  explicit WandererControllerImpl(core::IWandererCore_uptr core);

  /**
   * Returns the desktop display mode.
   *
   * @return the desktop display mode.
   * @throws BadStateException if the desktop info cannot be deduced.
   * @since 0.1.0
   */
  SDL_DisplayMode GetDesktopInfo();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @param core a unique pointer to the associated core instance.
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @throws NullPointerException if the supplied pointer is nullptr.
   * @since 0.1.0
   */
  friend IWandererController_uptr CreateController(core::IWandererCore_uptr core);

  ~WandererControllerImpl() override;

  void Run() override;

  void Quit() override;

  void MovePlayer(core::Direction direction) override;

  void StopPlayer(core::Direction direction) override;
};

}
