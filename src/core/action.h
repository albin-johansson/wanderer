#pragma once

#include <SDL.h>

#include <json.hpp>

#include "wanderer_stdinc.h"

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

class IAction {
 public:
  virtual ~IAction() noexcept = default;

  virtual void execute() = 0;
};

void from_json(const nlohmann::json& json, ActionID& action);

}  // namespace albinjohansson::wanderer
