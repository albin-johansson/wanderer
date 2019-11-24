#pragma once
#include "entity_state.h"
#include "entity_state_machine.h"

namespace albinjohansson::wanderer {

class EntityMoveDelegate final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  explicit EntityMoveDelegate(IEntityStateMachine* parent);

  ~EntityMoveDelegate() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const ILevel& level) override;

  void Exit(const ILevel& level) override;

  void Tick(const ILevel& level, float delta) override;

  [[nodiscard]] inline IEntity& GetEntity() { return parent->GetEntity(); }

  [[nodiscard]] IEntityStateMachine& GetParent() noexcept { return *parent; }
};

}
