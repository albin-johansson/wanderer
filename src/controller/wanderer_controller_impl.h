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
  static constexpr double MAX_FRAME_TIME = 0.25;
  static constexpr double MIN_FRAME_TIME = 0.0083; // limited at approx 120 FPS
  bool running = false;

  core::IWandererCore_uptr core = nullptr;
  visuals::Window_uptr window = nullptr;
  visuals::Renderer_uptr renderer = nullptr;
  KeyStateManager_uptr keyStateManager = nullptr;

  PlayerController playerController;

  explicit WandererControllerImpl(core::IWandererCore_uptr core);

  void UpdateInput();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @param core the associated IWandererCore instance.
   * @return a unique pointer to an IWandererController instance.
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
