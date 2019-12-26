#pragma once
#include "entity_state.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

class EntityMoveDelegate final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  explicit EntityMoveDelegate(IEntityStateMachine* parent);

  ~EntityMoveDelegate() override;

  void Draw(const Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

  void Tick(const IWandererCore& core, float delta) override;

  void UpdateAnimation();

  void UpdatePosition(float delta);

  [[nodiscard]] IEntityStateMachine& GetParent() noexcept;
};

}
