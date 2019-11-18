#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"

namespace wanderer::core {

class EntityIdleDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;

 public:
  EntityIdleDelegate(IEntity* entity, IEntityStateMachine* parent);

  ~EntityIdleDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter() override;

  void Exit() override;

  void Tick(float delta) override;

  [[nodiscard]] inline IEntityStateMachine* GetParent() noexcept { return parent; }
};

}
