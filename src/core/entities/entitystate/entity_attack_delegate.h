#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "animation.h"

namespace wanderer::core {

class EntityAttackDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;
  visuals::Animation animation;

 public:
  EntityAttackDelegate(IEntity* entity, IEntityStateMachine* parent);

  ~EntityAttackDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter() override;

  void Exit() override;

  void Tick(float delta) override;

};

}
