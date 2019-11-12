#pragma once
#include <memory>
#include "tickable.h"
#include "entity_state_id.h"
#include "input.h"

namespace wanderer::core {

class IEntityStateMachine : public ITickable {
 protected:
  IEntityStateMachine() = default;

 public:
  ~IEntityStateMachine() override = default;

  virtual void HandleInput(const Input& input) = 0;

  virtual void Change(EntityStateID id) = 0;

};

using IEntityStateMachine_uptr = std::unique_ptr<IEntityStateMachine>;

}
