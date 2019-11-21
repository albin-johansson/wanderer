#pragma once
#include "entity_state.h"
#include "entity_attack_delegate.h"
#include "entity_state_machine.h"

namespace wanderer::core {

class SkeletonAttackState final : public IEntityState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  explicit SkeletonAttackState(IEntityStateMachine* parent);

  ~SkeletonAttackState() override;

  void Tick(const IGame& game, float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

};

}
