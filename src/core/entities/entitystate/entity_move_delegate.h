#pragma once
#include "entity_state.h"
#include "entity_state_machine.h"

namespace wanderer::core {

class EntityMoveDelegate final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  explicit EntityMoveDelegate(IEntityStateMachine* parent);

  ~EntityMoveDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IGame& world) override;

  void Exit(const IGame& world) override;

  void Tick(const IGame& game, float delta) override;

  [[nodiscard]] inline IEntity& GetEntity() { return parent->GetEntity(); }
};

}
