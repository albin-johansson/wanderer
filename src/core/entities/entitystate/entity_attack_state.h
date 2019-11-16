#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "animation.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

class EntityAttackState final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;
  visuals::Animation animation;
  EntityDrawDelegate drawDelegate;

 public :
  EntityAttackState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityAttackState() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void HandleInput(const Input& input) override;

  void Enter() override;

  void Exit() override;

  void Tick(float delta) override;
};

}
