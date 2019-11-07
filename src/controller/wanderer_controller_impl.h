#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"

namespace wanderer::controller {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  core::IWandererCore_uptr core = nullptr;

  WandererControllerImpl();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @return a unique pointer to an IWandererController instance.
   * @since 0.1.0
   */
  friend IWandererController_uptr CreateController();

  ~WandererControllerImpl() override;

  void Run() override;

  void Quit() override;
};

}
