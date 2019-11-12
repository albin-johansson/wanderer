#pragma once
#include "entity_state_machine.h"
#include "entity_state.h"
#include <memory>
#include <map>
#include "entity.h"

namespace wanderer::core {

class EntityStateMachineImpl final : public IEntityStateMachine {
 private:
  std::map<EntityStateID, IEntityState_sptr> states;
  IEntityState_sptr currentState = nullptr;
  IEntity* entity = nullptr;

  void Put(EntityStateID id, IEntityState_sptr state);

 public:
  explicit EntityStateMachineImpl(IEntity* entity);

  ~EntityStateMachineImpl() override;

  void HandleInput(const Input& input) override;

  void Change(EntityStateID id) override;

  void Tick(float delta) override;
};

}
