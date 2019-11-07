#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"

namespace wanderer::controller {

class WandererControllerImpl final : public IWandererController {
 private:
  core::IWandererCore_uptr core = nullptr;

  WandererControllerImpl();

 public:
  friend IWandererController_uptr CreateController();

  ~WandererControllerImpl() override;

  void Run() override;

  void Quit() override;
};

}
