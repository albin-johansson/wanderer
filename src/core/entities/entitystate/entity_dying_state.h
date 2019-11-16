#pragma once
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_state.h"
#include "entity_draw_delegate.h"
#include "animation.h"

namespace wanderer::core {

class EntityDyingState final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;
  EntityDrawDelegate drawDelegate;
  visuals::Animation animation;

 public:
  EntityDyingState(IEntity* entity, IEntityStateMachine* parent);

  ~EntityDyingState() override;

  void Tick(float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void HandleInput(const Input& input) override;

  void Enter() override;

  void Exit() override;

};

}
