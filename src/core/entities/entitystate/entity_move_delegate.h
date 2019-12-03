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

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

  void Tick(const IWandererCore& core, float delta) override;

  [[nodiscard]] inline IEntity& GetEntity() { return parent->GetEntity(); }

  [[nodiscard]] IEntityStateMachine& GetParent() noexcept { return *parent; }
};

}
