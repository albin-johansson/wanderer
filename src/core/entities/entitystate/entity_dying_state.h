#pragma once
#include "abstract_entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"

namespace wanderer::core {

class EntityDyingState final : public AbstractEntityState {
 public:
  EntityDyingState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityDyingState() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void HandleInput(const Input& input) override;

  void Tick(float delta) override;

  void Enter() override;

  void Exit() override;
};

}
