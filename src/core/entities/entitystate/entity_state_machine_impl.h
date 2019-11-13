#pragma once
#include "entity_state_machine.h"
#include "entity_state.h"
#include <memory>
#include <map>
#include "entity.h"

namespace wanderer::core {

/**
 * The EntityStateMachineImpl class is an implementation of the IEntityStateMachine interface.
 *
 * @see IEntityStateMachine
 * @since 0.1.0
 */
class EntityStateMachineImpl final : public IEntityStateMachine {
 private:
  std::map<EntityStateID, IEntityState_sptr> states;
  IEntityState_sptr currentState = nullptr;
  IEntity* entity = nullptr;

  void Put(EntityStateID id, IEntityState_sptr state);

 public:
  /**
   * @param entity a pointer to the associated entity instance, will not be freed by the created
   * state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityStateMachineImpl(IEntity* entity);

  ~EntityStateMachineImpl() override;

  void HandleInput(const Input& input) override;

  void Change(EntityStateID id) override;

  void Tick(float delta) override;
};

}
