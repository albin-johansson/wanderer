#pragma once
#include "key_state_manager.h"
#include "wanderer_controller.h"

namespace wanderer::controller {

class PlayerController final {
 private:
  IWandererController* controller = nullptr;

  void CheckPressed(const KeyStateManager& keyStateManager);

  void CheckReleased(const KeyStateManager& keyStateManager);

 public:
  PlayerController(IWandererController* controller);

  ~PlayerController();

  void Update(const KeyStateManager& keyStateManager);
};

}
