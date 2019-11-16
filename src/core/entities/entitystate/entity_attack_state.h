#pragma once
#include "abstract_entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"

namespace wanderer::core {

class EntityAttackState final : public AbstractEntityState {
 public :
  EntityAttackState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityAttackState() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void HandleInput(const Input& input) override;

  void Tick(float delta) override;

  void Enter() override;

  void Exit() override;

};

}
