#pragma once

#include <SDL.h>

#include "input.h"
#include "menu_id.h"
#include "menu_state_machine.h"
#include "wanderer_core.h"

namespace albinjohansson::wanderer {

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
  PlayerAttack,
  PlayerInteract,
};

inline ActionID to_action(const std::string& id)
{
  if (id == "Quit") {
    return ActionID::Quit;
  } else if (id == "GotoHome") {
    return ActionID::GotoHome;
  } else if (id == "GotoSettings") {
    return ActionID::GotoSettings;
  } else if (id == "GotoControls") {
    return ActionID::GotoControls;
  } else if (id == "GotoInGame") {
    return ActionID::GotoInGame;
  } else if (id == "GotoCredits") {
    return ActionID::GotoCredits;
  }

  throw std::logic_error{"Failed to determine action ID!"};
}

class IAction {
 public:
  virtual ~IAction() = default;

  virtual void execute() = 0;
};

class MenuAction: public IAction {
 public:

 private:


};

}  // namespace albinjohansson::wanderer
