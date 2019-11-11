#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "window.h"
#include "key_state_manager.h"
#include "player_controller.h"

namespace wanderer::controller {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  /**
   * A constant that denotes the maximum allowed frame time (delta time) in seconds. This is used
   * to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  static constexpr double MAX_FRAME_TIME = 0.25;

  bool running = false;

  core::IWandererCore_uptr core = nullptr;
  visuals::Window_uptr window = nullptr;
  visuals::Renderer_uptr renderer = nullptr;
  KeyStateManager_uptr keyStateManager = nullptr;
  PlayerController playerController;

  /**
   * @param core a unique pointer to the associated core instance.
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @throws NullPointerException if the supplied pointer is nullptr.
   * @since 0.1.0
   */
  explicit WandererControllerImpl(core::IWandererCore_uptr core);

  void UpdateInput();

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
