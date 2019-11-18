#pragma once
#include "entity_state_machine.h"
#include "input.h"
#include <memory>

namespace wanderer::core {

class IPlayerStateMachine : public IEntityStateMachine {
 protected:
  IPlayerStateMachine() = default;

 public:
  ~IPlayerStateMachine() override = default;

  virtual void HandleInput(const Input& input) = 0;
};

using IPlayerStateMachine_uptr = std::unique_ptr<IPlayerStateMachine>;
using IPlayerStateMachine_sptr = std::shared_ptr<IPlayerStateMachine>;
using IPlayerStateMachine_wptr = std::weak_ptr<IPlayerStateMachine>;

}
