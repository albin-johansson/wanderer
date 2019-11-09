#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "window.h"

namespace wanderer::controller {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  static constexpr float MAX_FRAME_TIME = 0.25f;
//  float accumulator = 0;
  bool running = false;

  core::IWandererCore_uptr core = nullptr;
  view::Window_uptr window = nullptr;
  view::Renderer_uptr renderer = nullptr;

  explicit WandererControllerImpl(core::IWandererCore_uptr core);

  void HandleInput();

  void SavePositions();

  void Update(float delta);

  void Render(float delta);

  void Interpolate(float alpha);

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

};

}
