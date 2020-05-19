#pragma once

#include "wanderer_stdinc.h"

namespace wanderer {

enum class ActionID {
  Quit,

  // Menu actions
  GotoHome,
  GotoSettings,
  GotoControls,
  GotoInGame,
  GotoCredits,
  GotoInventory,

  // Player actions
  //  PlayerAttack,
  //  PlayerInteract,
};

WANDERER_SERIALIZE_ENUM(ActionID,
                        {{ActionID::Quit, "Quit"},
                         {ActionID::GotoHome, "GotoHome"},
                         {ActionID::GotoSettings, "GotoSettings"},
                         {ActionID::GotoControls, "GotoControls"},
                         {ActionID::GotoInGame, "GotoInGame"},
                         {ActionID::GotoCredits, "GotoCredits"},
                         {ActionID::GotoInventory, "GotoInventory"}})

class IAction {
 public:
  virtual ~IAction() noexcept = default;

  virtual void execute() = 0;
};

}  // namespace wanderer
